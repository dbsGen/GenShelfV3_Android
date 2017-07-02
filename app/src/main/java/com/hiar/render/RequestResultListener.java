package com.hiar.render;

/**
 * Created by mac on 2017/5/29.
 */

public class RequestResultListener implements Request.OnStatusListener {
    private long nativePtr;

    private native void process(long ptr, float percent);
    private native void complete(long ptr, Request request);
    private native void failed(long ptr);
    private native void cancel(long ptr);

    @Override
    public void onProgress(Request request, float percent) {
        process(nativePtr, percent);
    }

    @Override
    public void onComplete(Request request) {
        complete(nativePtr, request);
    }

    @Override
    public void onFailed(Exception e) {
        failed(nativePtr);
    }

    @Override
    public void onCancel(Request request) {
        cancel(nativePtr);
    }

    public RequestResultListener(long ptr) {
        nativePtr = ptr;
    }
}
