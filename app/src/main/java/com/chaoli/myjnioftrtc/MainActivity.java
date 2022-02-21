package com.chaoli.myjnioftrtc;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.QuickContactBadge;
import android.widget.TextView;
import android.widget.Toast;

import com.chaoli.myjnioftrtc.databinding.ActivityMainBinding;
import com.chaoli.myjnioftrtc.nativeUtils.JniCallBack;
import com.chaoli.myjnioftrtc.nativeUtils.TRTCNativeManager;
import com.tencent.trtc.TRTCCloud;
import com.tencent.trtc.TRTCCloudDef;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    protected static final int REQ_PERMISSION_CODE = 0x1000;
    // 权限个数计数，获取Android系统权限
    protected int mGrantedCount = 0;

    protected int mLogLevel = 0;


    private ActivityMainBinding binding;
    private boolean inRoomFlag = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.hide(); //隐藏标题栏
        }

        binding.btEnterRoom.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(inRoomFlag){
                    exitRoom();
                }else{
                    enterRoom();
                }

            }
        });

        binding.btLogView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mLogLevel = (mLogLevel + 1) % 3;
                TRTCNativeManager.showDebugView(mLogLevel);

            }
        });

        // Example of a call to a native method

        checkPermission();

    }

    private void exitRoom() {
        TRTCNativeManager.stopLocalAudio();
        TRTCNativeManager.stopLocalPreview();
        TRTCNativeManager.exitRoom();
    }

    //////////////////////////////////    动态权限申请   ////////////////////////////////////////

    protected boolean checkPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            List<String> permissions = new ArrayList<>();
            if (PackageManager.PERMISSION_GRANTED != ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                permissions.add(Manifest.permission.WRITE_EXTERNAL_STORAGE);
            }
            if (PackageManager.PERMISSION_GRANTED != ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA)) {
                permissions.add(Manifest.permission.CAMERA);
            }
            if (PackageManager.PERMISSION_GRANTED != ActivityCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO)) {
                permissions.add(Manifest.permission.RECORD_AUDIO);
            }
            if (PackageManager.PERMISSION_GRANTED != ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE)) {
                permissions.add(Manifest.permission.READ_EXTERNAL_STORAGE);
            }
            if (permissions.size() != 0) {
                ActivityCompat.requestPermissions(this,
                        permissions.toArray(new String[0]),
                        REQ_PERMISSION_CODE);
                return false;
            }
        }
        return true;
    }
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode) {
            case REQ_PERMISSION_CODE:
                for (int ret : grantResults) {
                    if (PackageManager.PERMISSION_GRANTED == ret) {
                        mGrantedCount++;
                    }
                }
                if (mGrantedCount == permissions.length) {

                } else {
                    Toast.makeText(this, "用户没有允许需要的权限，加入通话失败", Toast.LENGTH_SHORT).show();
                }
                mGrantedCount = 0;
                break;
            default:
                break;
        }
    }

    private void enterRoom() {
        String roomid = binding.etRoomid.getText().toString();
        String userid = binding.etUserid.getText().toString();

        if(roomid.isEmpty())roomid = "9527";
        if(userid.isEmpty())userid = System.currentTimeMillis()+"";

        TRTCNativeManager.startLocalPreview(true,binding.localView);
        TRTCNativeManager.startLocalAudio();
        TRTCNativeManager.enterRoom(roomid,userid,GenerateTestUserSig.genTestUserSig(userid),GenerateTestUserSig.SDKAPPID);
        JniCallBack.setCallback(new JniCallBack.callBack() {
            @Override
            public void onUserVideoAvailable(String userId, boolean available) {
                if(available){
                    TRTCNativeManager.startRemoteView(userId, binding.remoteView);
                }else{
                    TRTCNativeManager.stopRemoteView(userId);
                }

            }

            @Override
            public void onEnterRoom(int result) {
                if(result>0){
                    inRoomFlag =true;
                    binding.btEnterRoom.setText("退房");
                }else{
                    inRoomFlag =false;
                    binding.btEnterRoom.setText("进房");
                }
            }

            @Override
            public void onExitRoom(int reason) {
                inRoomFlag =false;
                binding.btEnterRoom.setText("进房");
            }
        });
    }


    /**
     * A native method that is implemented by the 'myjnioftrtc' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();


    @Override
    protected void onDestroy() {
        super.onDestroy();
        exitRoom();

    }
}