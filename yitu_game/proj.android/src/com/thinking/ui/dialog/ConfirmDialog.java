package com.thinking.ui.dialog;

import com.thinking.yitu_game.R;

import android.app.Dialog;
import android.content.Context;
import android.view.Window;
import android.widget.Button;
import android.widget.TextView;

public class ConfirmDialog extends Dialog
{
	public Button btn_yes;
	public Button btn_calcel;
	public TextView txt_info;

	private static ConfirmDialog dia = null;
	private static int count = 0;

	private ConfirmDialog(Context context)
	{
		super(context);
		super.requestWindowFeature(Window.FEATURE_NO_TITLE);
		super.setContentView(R.layout.dia_confirm);
		btn_calcel = (Button) this.findViewById(R.id.btn_cancel);
		btn_yes = (Button) this.findViewById(R.id.btn_yes);
		txt_info = (TextView) this.findViewById(R.id.txt_message);
	}

	public static ConfirmDialog getConfirmDialogDialog(Context context)
	{
		if (dia == null)
			dia = new ConfirmDialog(context);
		return dia;
	}

	public void show()
	{
		count++;
		if (count >= 2)
			return;
		else
			super.show();
	}

	public void cancel()
	{
		count--;
		super.cancel();
	}

	public void setMsg(String msg)
	{
		txt_info.setText(msg);
	}
}
