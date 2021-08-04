
namespace Bluetooth
{
    partial class Form1
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置受控資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
        /// 這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.btn_open = new System.Windows.Forms.Button();
            this.groupBox_connect = new System.Windows.Forms.GroupBox();
            this.button_refresh = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox_port = new System.Windows.Forms.ComboBox();
            this.btn_close = new System.Windows.Forms.Button();
            this.textBox_log = new System.Windows.Forms.TextBox();
            this.groupBox_log = new System.Windows.Forms.GroupBox();
            this.btn_shift = new System.Windows.Forms.Button();
            this.btn_ctrl = new System.Windows.Forms.Button();
            this.btn_enter = new System.Windows.Forms.Button();
            this.btn_down = new System.Windows.Forms.Button();
            this.btn_up = new System.Windows.Forms.Button();
            this.btn_left = new System.Windows.Forms.Button();
            this.btn_right = new System.Windows.Forms.Button();
            this.btn_space = new System.Windows.Forms.Button();
            this.btn_A = new System.Windows.Forms.Button();
            this.btn_W = new System.Windows.Forms.Button();
            this.btn_S = new System.Windows.Forms.Button();
            this.btn_D = new System.Windows.Forms.Button();
            this.groupBox_control = new System.Windows.Forms.GroupBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.btn_E = new System.Windows.Forms.Button();
            this.btn_Q = new System.Windows.Forms.Button();
            this.btn_C = new System.Windows.Forms.Button();
            this.btn_Z = new System.Windows.Forms.Button();
            this.btn_R = new System.Windows.Forms.Button();
            this.groupBox_connect.SuspendLayout();
            this.groupBox_log.SuspendLayout();
            this.groupBox_control.SuspendLayout();
            this.SuspendLayout();
            // 
            // btn_open
            // 
            this.btn_open.Location = new System.Drawing.Point(32, 211);
            this.btn_open.Name = "btn_open";
            this.btn_open.Size = new System.Drawing.Size(139, 81);
            this.btn_open.TabIndex = 5;
            this.btn_open.TabStop = false;
            this.btn_open.Text = "Open";
            this.btn_open.UseVisualStyleBackColor = true;
            this.btn_open.Click += new System.EventHandler(this.btn_open_Click);
            // 
            // groupBox_connect
            // 
            this.groupBox_connect.Controls.Add(this.button_refresh);
            this.groupBox_connect.Controls.Add(this.label1);
            this.groupBox_connect.Controls.Add(this.comboBox_port);
            this.groupBox_connect.Controls.Add(this.btn_close);
            this.groupBox_connect.Controls.Add(this.btn_open);
            this.groupBox_connect.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox_connect.Location = new System.Drawing.Point(44, 52);
            this.groupBox_connect.Name = "groupBox_connect";
            this.groupBox_connect.Size = new System.Drawing.Size(567, 322);
            this.groupBox_connect.TabIndex = 6;
            this.groupBox_connect.TabStop = false;
            this.groupBox_connect.Text = "Bluetooth Connection";
            // 
            // button_refresh
            // 
            this.button_refresh.Location = new System.Drawing.Point(372, 211);
            this.button_refresh.Name = "button_refresh";
            this.button_refresh.Size = new System.Drawing.Size(164, 81);
            this.button_refresh.TabIndex = 9;
            this.button_refresh.TabStop = false;
            this.button_refresh.Text = "Refresh";
            this.button_refresh.UseVisualStyleBackColor = true;
            this.button_refresh.Click += new System.EventHandler(this.button_refresh_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 63);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(158, 38);
            this.label1.TabIndex = 8;
            this.label1.Text = "COM port";
            // 
            // comboBox_port
            // 
            this.comboBox_port.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_port.FormattingEnabled = true;
            this.comboBox_port.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.comboBox_port.Location = new System.Drawing.Point(32, 127);
            this.comboBox_port.Name = "comboBox_port";
            this.comboBox_port.Size = new System.Drawing.Size(504, 46);
            this.comboBox_port.Sorted = true;
            this.comboBox_port.TabIndex = 7;
            this.comboBox_port.TabStop = false;
            // 
            // btn_close
            // 
            this.btn_close.Enabled = false;
            this.btn_close.Location = new System.Drawing.Point(202, 211);
            this.btn_close.Name = "btn_close";
            this.btn_close.Size = new System.Drawing.Size(139, 81);
            this.btn_close.TabIndex = 6;
            this.btn_close.TabStop = false;
            this.btn_close.Text = "Close";
            this.btn_close.UseVisualStyleBackColor = true;
            this.btn_close.Click += new System.EventHandler(this.btn_close_Click);
            // 
            // textBox_log
            // 
            this.textBox_log.Location = new System.Drawing.Point(42, 63);
            this.textBox_log.Multiline = true;
            this.textBox_log.Name = "textBox_log";
            this.textBox_log.ReadOnly = true;
            this.textBox_log.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox_log.Size = new System.Drawing.Size(630, 544);
            this.textBox_log.TabIndex = 9;
            this.textBox_log.TabStop = false;
            this.textBox_log.TextChanged += new System.EventHandler(this.textBox_log_TextChanged);
            this.textBox_log.Leave += new System.EventHandler(this.textBox_log_Leave);
            // 
            // groupBox_log
            // 
            this.groupBox_log.Controls.Add(this.textBox_log);
            this.groupBox_log.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox_log.Location = new System.Drawing.Point(661, 52);
            this.groupBox_log.Name = "groupBox_log";
            this.groupBox_log.Size = new System.Drawing.Size(717, 646);
            this.groupBox_log.TabIndex = 10;
            this.groupBox_log.TabStop = false;
            this.groupBox_log.Text = "Log";
            // 
            // btn_shift
            // 
            this.btn_shift.BackColor = System.Drawing.Color.Black;
            this.btn_shift.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_shift.ForeColor = System.Drawing.Color.White;
            this.btn_shift.Location = new System.Drawing.Point(962, 169);
            this.btn_shift.Name = "btn_shift";
            this.btn_shift.Size = new System.Drawing.Size(327, 90);
            this.btn_shift.TabIndex = 30;
            this.btn_shift.TabStop = false;
            this.btn_shift.Text = "shift";
            this.btn_shift.UseVisualStyleBackColor = false;
            // 
            // btn_ctrl
            // 
            this.btn_ctrl.BackColor = System.Drawing.Color.Black;
            this.btn_ctrl.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_ctrl.ForeColor = System.Drawing.Color.White;
            this.btn_ctrl.Location = new System.Drawing.Point(777, 280);
            this.btn_ctrl.Name = "btn_ctrl";
            this.btn_ctrl.Size = new System.Drawing.Size(141, 116);
            this.btn_ctrl.TabIndex = 29;
            this.btn_ctrl.TabStop = false;
            this.btn_ctrl.Text = "ctrl";
            this.btn_ctrl.UseVisualStyleBackColor = false;
            // 
            // btn_enter
            // 
            this.btn_enter.BackColor = System.Drawing.Color.Black;
            this.btn_enter.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_enter.ForeColor = System.Drawing.Color.White;
            this.btn_enter.Location = new System.Drawing.Point(962, 46);
            this.btn_enter.Name = "btn_enter";
            this.btn_enter.Size = new System.Drawing.Size(327, 90);
            this.btn_enter.TabIndex = 28;
            this.btn_enter.TabStop = false;
            this.btn_enter.Text = "Enter";
            this.btn_enter.UseVisualStyleBackColor = false;
            // 
            // btn_down
            // 
            this.btn_down.BackColor = System.Drawing.Color.Black;
            this.btn_down.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_down.ForeColor = System.Drawing.Color.White;
            this.btn_down.Location = new System.Drawing.Point(1080, 341);
            this.btn_down.Name = "btn_down";
            this.btn_down.Size = new System.Drawing.Size(97, 55);
            this.btn_down.TabIndex = 27;
            this.btn_down.TabStop = false;
            this.btn_down.Text = "↓";
            this.btn_down.UseVisualStyleBackColor = false;
            // 
            // btn_up
            // 
            this.btn_up.BackColor = System.Drawing.Color.Black;
            this.btn_up.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_up.ForeColor = System.Drawing.Color.White;
            this.btn_up.Location = new System.Drawing.Point(1080, 280);
            this.btn_up.Name = "btn_up";
            this.btn_up.Size = new System.Drawing.Size(97, 55);
            this.btn_up.TabIndex = 26;
            this.btn_up.TabStop = false;
            this.btn_up.Text = "↑";
            this.btn_up.UseVisualStyleBackColor = false;
            // 
            // btn_left
            // 
            this.btn_left.BackColor = System.Drawing.Color.Black;
            this.btn_left.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_left.ForeColor = System.Drawing.Color.White;
            this.btn_left.Location = new System.Drawing.Point(962, 280);
            this.btn_left.Name = "btn_left";
            this.btn_left.Size = new System.Drawing.Size(97, 116);
            this.btn_left.TabIndex = 25;
            this.btn_left.TabStop = false;
            this.btn_left.Text = "←";
            this.btn_left.UseVisualStyleBackColor = false;
            // 
            // btn_right
            // 
            this.btn_right.BackColor = System.Drawing.Color.Black;
            this.btn_right.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_right.ForeColor = System.Drawing.Color.White;
            this.btn_right.Location = new System.Drawing.Point(1192, 280);
            this.btn_right.Name = "btn_right";
            this.btn_right.Size = new System.Drawing.Size(97, 116);
            this.btn_right.TabIndex = 24;
            this.btn_right.TabStop = false;
            this.btn_right.Text = "→";
            this.btn_right.UseVisualStyleBackColor = false;
            // 
            // btn_space
            // 
            this.btn_space.BackColor = System.Drawing.Color.Black;
            this.btn_space.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_space.ForeColor = System.Drawing.Color.White;
            this.btn_space.Location = new System.Drawing.Point(430, 306);
            this.btn_space.Name = "btn_space";
            this.btn_space.Size = new System.Drawing.Size(318, 90);
            this.btn_space.TabIndex = 23;
            this.btn_space.TabStop = false;
            this.btn_space.Text = "︺";
            this.btn_space.UseVisualStyleBackColor = false;
            // 
            // btn_A
            // 
            this.btn_A.BackColor = System.Drawing.Color.Black;
            this.btn_A.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_A.ForeColor = System.Drawing.Color.White;
            this.btn_A.Location = new System.Drawing.Point(46, 190);
            this.btn_A.Name = "btn_A";
            this.btn_A.Size = new System.Drawing.Size(97, 90);
            this.btn_A.TabIndex = 20;
            this.btn_A.TabStop = false;
            this.btn_A.Text = "A";
            this.btn_A.UseVisualStyleBackColor = false;
            // 
            // btn_W
            // 
            this.btn_W.BackColor = System.Drawing.Color.Black;
            this.btn_W.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_W.ForeColor = System.Drawing.Color.White;
            this.btn_W.Location = new System.Drawing.Point(167, 77);
            this.btn_W.Name = "btn_W";
            this.btn_W.Size = new System.Drawing.Size(97, 90);
            this.btn_W.TabIndex = 19;
            this.btn_W.TabStop = false;
            this.btn_W.Text = "W";
            this.btn_W.UseVisualStyleBackColor = false;
            // 
            // btn_S
            // 
            this.btn_S.BackColor = System.Drawing.Color.Black;
            this.btn_S.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_S.ForeColor = System.Drawing.Color.White;
            this.btn_S.Location = new System.Drawing.Point(167, 190);
            this.btn_S.Name = "btn_S";
            this.btn_S.Size = new System.Drawing.Size(97, 90);
            this.btn_S.TabIndex = 21;
            this.btn_S.TabStop = false;
            this.btn_S.Text = "S";
            this.btn_S.UseVisualStyleBackColor = false;
            // 
            // btn_D
            // 
            this.btn_D.BackColor = System.Drawing.Color.Black;
            this.btn_D.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_D.ForeColor = System.Drawing.Color.White;
            this.btn_D.Location = new System.Drawing.Point(289, 190);
            this.btn_D.Name = "btn_D";
            this.btn_D.Size = new System.Drawing.Size(97, 90);
            this.btn_D.TabIndex = 22;
            this.btn_D.TabStop = false;
            this.btn_D.Text = "D";
            this.btn_D.UseVisualStyleBackColor = false;
            // 
            // groupBox_control
            // 
            this.groupBox_control.Controls.Add(this.btn_R);
            this.groupBox_control.Controls.Add(this.btn_Z);
            this.groupBox_control.Controls.Add(this.btn_C);
            this.groupBox_control.Controls.Add(this.btn_Q);
            this.groupBox_control.Controls.Add(this.btn_E);
            this.groupBox_control.Controls.Add(this.btn_shift);
            this.groupBox_control.Controls.Add(this.btn_right);
            this.groupBox_control.Controls.Add(this.btn_ctrl);
            this.groupBox_control.Controls.Add(this.btn_D);
            this.groupBox_control.Controls.Add(this.btn_enter);
            this.groupBox_control.Controls.Add(this.btn_S);
            this.groupBox_control.Controls.Add(this.btn_down);
            this.groupBox_control.Controls.Add(this.btn_W);
            this.groupBox_control.Controls.Add(this.btn_up);
            this.groupBox_control.Controls.Add(this.btn_A);
            this.groupBox_control.Controls.Add(this.btn_left);
            this.groupBox_control.Controls.Add(this.btn_space);
            this.groupBox_control.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox_control.Location = new System.Drawing.Point(44, 713);
            this.groupBox_control.Name = "groupBox_control";
            this.groupBox_control.Size = new System.Drawing.Size(1334, 428);
            this.groupBox_control.TabIndex = 31;
            this.groupBox_control.TabStop = false;
            this.groupBox_control.Text = "Keyboard";
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // btn_E
            // 
            this.btn_E.BackColor = System.Drawing.Color.Black;
            this.btn_E.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_E.ForeColor = System.Drawing.Color.White;
            this.btn_E.Location = new System.Drawing.Point(289, 77);
            this.btn_E.Name = "btn_E";
            this.btn_E.Size = new System.Drawing.Size(97, 90);
            this.btn_E.TabIndex = 31;
            this.btn_E.TabStop = false;
            this.btn_E.Text = "E";
            this.btn_E.UseVisualStyleBackColor = false;
            // 
            // btn_Q
            // 
            this.btn_Q.BackColor = System.Drawing.Color.Black;
            this.btn_Q.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_Q.ForeColor = System.Drawing.Color.White;
            this.btn_Q.Location = new System.Drawing.Point(46, 77);
            this.btn_Q.Name = "btn_Q";
            this.btn_Q.Size = new System.Drawing.Size(97, 90);
            this.btn_Q.TabIndex = 32;
            this.btn_Q.TabStop = false;
            this.btn_Q.Text = "Q";
            this.btn_Q.UseVisualStyleBackColor = false;
            // 
            // btn_C
            // 
            this.btn_C.BackColor = System.Drawing.Color.Black;
            this.btn_C.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_C.ForeColor = System.Drawing.Color.White;
            this.btn_C.Location = new System.Drawing.Point(289, 306);
            this.btn_C.Name = "btn_C";
            this.btn_C.Size = new System.Drawing.Size(97, 90);
            this.btn_C.TabIndex = 34;
            this.btn_C.TabStop = false;
            this.btn_C.Text = "C";
            this.btn_C.UseVisualStyleBackColor = false;
            // 
            // btn_Z
            // 
            this.btn_Z.BackColor = System.Drawing.Color.Black;
            this.btn_Z.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_Z.ForeColor = System.Drawing.Color.White;
            this.btn_Z.Location = new System.Drawing.Point(46, 306);
            this.btn_Z.Name = "btn_Z";
            this.btn_Z.Size = new System.Drawing.Size(97, 90);
            this.btn_Z.TabIndex = 35;
            this.btn_Z.TabStop = false;
            this.btn_Z.Text = "Z";
            this.btn_Z.UseVisualStyleBackColor = false;
            // 
            // btn_R
            // 
            this.btn_R.BackColor = System.Drawing.Color.Black;
            this.btn_R.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_R.ForeColor = System.Drawing.Color.White;
            this.btn_R.Location = new System.Drawing.Point(430, 77);
            this.btn_R.Name = "btn_R";
            this.btn_R.Size = new System.Drawing.Size(97, 90);
            this.btn_R.TabIndex = 36;
            this.btn_R.TabStop = false;
            this.btn_R.Text = "R";
            this.btn_R.UseVisualStyleBackColor = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(16F, 30F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1428, 1188);
            this.Controls.Add(this.groupBox_log);
            this.Controls.Add(this.groupBox_connect);
            this.Controls.Add(this.groupBox_control);
            this.KeyPreview = true;
            this.Name = "Form1";
            this.Text = "ControlPanel";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyUp);
            this.groupBox_connect.ResumeLayout(false);
            this.groupBox_connect.PerformLayout();
            this.groupBox_log.ResumeLayout(false);
            this.groupBox_log.PerformLayout();
            this.groupBox_control.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button btn_open;
        private System.Windows.Forms.GroupBox groupBox_connect;
        private System.Windows.Forms.Button btn_close;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_log;
        private System.Windows.Forms.GroupBox groupBox_log;
        private System.Windows.Forms.Button btn_shift;
        private System.Windows.Forms.Button btn_ctrl;
        private System.Windows.Forms.Button btn_enter;
        private System.Windows.Forms.Button btn_down;
        private System.Windows.Forms.Button btn_up;
        private System.Windows.Forms.Button btn_left;
        private System.Windows.Forms.Button btn_right;
        private System.Windows.Forms.Button btn_space;
        private System.Windows.Forms.Button btn_A;
        private System.Windows.Forms.Button btn_W;
        private System.Windows.Forms.Button btn_S;
        private System.Windows.Forms.Button btn_D;
        private System.Windows.Forms.GroupBox groupBox_control;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button button_refresh;
        private System.Windows.Forms.ComboBox comboBox_port;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button btn_Z;
        private System.Windows.Forms.Button btn_C;
        private System.Windows.Forms.Button btn_Q;
        private System.Windows.Forms.Button btn_E;
        private System.Windows.Forms.Button btn_R;
    }
}

