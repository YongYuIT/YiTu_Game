/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import java.io.UnsupportedEncodingException;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import com.thinking.service.net.IOnLoginFinish;
import com.thinking.service.net.LoginTask;
import com.thinking.ui.dialog.ConfirmDialog;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;

public class AppActivity extends Cocos2dxActivity implements IOnLoginFinish
{
	// http://192.168.10.100:8081/login_service.ashx?method=login&check_num=1001&user_name=web_user&pass_wd=web_user

	// private native int do_btn_back();// 如果返回-1则表示需要退出游戏

	private Handler handler;

	private static AppActivity _currentActivity;

	public static Object getCurrentActivityObj()
	{
		return _currentActivity;
	}

	@Override
	protected void onCreate(final Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		AppActivity._currentActivity = this;
		handler = new Handler(this.getMainLooper());
	}

	public void do_OnBackDown()
	{

		Log.i("yitu------->if keyCode == KeyEvent.KEYCODE_BACK", "");

		myUpdateUIRunnable run = new myUpdateUIRunnable(AppActivity.this);
		try
		{
			handler.post(run);
		} catch (Exception e)
		{
			Log.e("fffffffuck", e.getMessage());
		}
	}

	public static Object test()
	{
		Log.i("fuck--------", "-----");
		return null;
	}

	public void do_login(String name, String passwd)
	{
		Log.i("from C++ is", "name=" + name + ",passwd=" + passwd);
		String path = "http://192.168.10.100:8081/login_service.ashx?method=login&check_num=1001&user_name="
				+ name + "&pass_wd=" + passwd;
		Log.i("path----->", path);
		LoginTask task = new LoginTask(this);
		task.execute(new String[] { path });
	}

	private native void on_login_finish(boolean result);

	@Override
	public void OnLoginFinish(String result)
	{
		Log.i("OnLoginFinish result------>", result + "");
		boolean res = false;
		if (result.trim().equals("success"))
			res = true;
		Log.i("on login finish------>", res + "");

		// this.on_login_finish(res);

		final boolean f_res = res;
		Cocos2dxGLSurfaceView.getInstance().queueEvent(new Runnable()
		{
			@Override
			public void run()
			{
				AppActivity.this.on_login_finish(f_res);
			}
		});

	}
}

class myUpdateUIRunnable implements Runnable
{
	private ConfirmDialog dia;
	private Context cont;

	public myUpdateUIRunnable(Context t)
	{
		cont = t;
	}

	@Override
	public void run()
	{
		dia = ConfirmDialog.getConfirmDialogDialog(cont);
		String s = "您确定退出游戏？";
		try
		{
			dia.txt_info.setText(new String(s.getBytes("utf-8"), "GBK"));
		} catch (UnsupportedEncodingException e)
		{
			dia.txt_info.setText(s);
		}
		dia.btn_calcel.setOnClickListener(new OnClickListener()
		{

			@Override
			public void onClick(View v)
			{
				myUpdateUIRunnable.this.dia.cancel();
			}
		});
		dia.show();
	}
}
