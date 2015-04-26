package com.thinking.service.net;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import android.os.AsyncTask;

public class LoginTask extends AsyncTask<String, Void, String>
{
	private IOnLoginFinish IOnObj;

	public LoginTask(IOnLoginFinish i)
	{
		this.IOnObj = i;
	}

	@Override
	protected String doInBackground(String... params)
	{
		try
		{
			URL url = new URL(params[0]);
			HttpURLConnection conn = (HttpURLConnection) url.openConnection();
			conn.setConnectTimeout(5000);
			if (conn.getResponseCode() == 200)
			{
				InputStream in = conn.getInputStream();
				String resultStr = "";
				byte[] buffer = new byte[1024 * 10];
				while (true)
				{
					int len = in.read(buffer);
					resultStr += (new String(buffer, "UTF-8")).trim();
					buffer = new byte[1024 * 10];
					if (len == -1)
					{
						break;
					}
				}
				in.close();
				return resultStr;
			} else
			{
				return "FAIL";
			}
		} catch (Exception e)
		{
			return "FAIL:" + e.getMessage();
		}
	}

	@Override
	protected void onPostExecute(String result)
	{
		IOnObj.OnLoginFinish(result);
	}
}
