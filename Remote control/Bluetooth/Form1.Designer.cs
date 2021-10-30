
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
            this.button_connection_refresh = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox_port = new System.Windows.Forms.ComboBox();
            this.btn_close = new System.Windows.Forms.Button();
            this.btn_A = new System.Windows.Forms.Button();
            this.btn_W = new System.Windows.Forms.Button();
            this.btn_S = new System.Windows.Forms.Button();
            this.btn_D = new System.Windows.Forms.Button();
            this.groupBox_control = new System.Windows.Forms.GroupBox();
            this.btn_R = new System.Windows.Forms.Button();
            this.btn_Z = new System.Windows.Forms.Button();
            this.btn_C = new System.Windows.Forms.Button();
            this.btn_Q = new System.Windows.Forms.Button();
            this.btn_E = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.trackBar_rotateArm = new System.Windows.Forms.TrackBar();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.textBox_rotateArm = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBox_cargo = new System.Windows.Forms.TextBox();
            this.trackBar_cargo = new System.Windows.Forms.TrackBar();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox_hand = new System.Windows.Forms.TextBox();
            this.textBox_3rdArm = new System.Windows.Forms.TextBox();
            this.textBox_2ndArm = new System.Windows.Forms.TextBox();
            this.textBox_1stArm = new System.Windows.Forms.TextBox();
            this.trackBar_3rdArm = new System.Windows.Forms.TrackBar();
            this.trackBar_2ndArm = new System.Windows.Forms.TrackBar();
            this.trackBar_1stArm = new System.Windows.Forms.TrackBar();
            this.trackBar_hand = new System.Windows.Forms.TrackBar();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.glControl_sideView = new OpenTK.GLControl();
            this.glControl_topView = new OpenTK.GLControl();
            this.Sensor_right_behind_behind = new System.Windows.Forms.Button();
            this.Sensor_left_behind_behind = new System.Windows.Forms.Button();
            this.Sensor_left_front_front = new System.Windows.Forms.Button();
            this.Sensor_right_front_front = new System.Windows.Forms.Button();
            this.Sensor_left_front_left = new System.Windows.Forms.Button();
            this.Sensor_right_front_right = new System.Windows.Forms.Button();
            this.btn_ResetArm = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.btn_delete = new System.Windows.Forms.Button();
            this.btn_Create = new System.Windows.Forms.Button();
            this.btn_choseSaveFile = new System.Windows.Forms.Button();
            this.textBox_createFileName = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.btn_saveData = new System.Windows.Forms.Button();
            this.btn_delData = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.textBox_FileName = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.textBox_FilePath = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBox_data_num = new System.Windows.Forms.TextBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.groupBox13 = new System.Windows.Forms.GroupBox();
            this.Example_Red = new System.Windows.Forms.Button();
            this.label25 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.Example_Green = new System.Windows.Forms.Button();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.Sensor_right_behind_ground = new System.Windows.Forms.Button();
            this.Sensor_right_behind_right = new System.Windows.Forms.Button();
            this.label27 = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.Sensor_left_behind_ground = new System.Windows.Forms.Button();
            this.Sensor_left_behind_left = new System.Windows.Forms.Button();
            this.label21 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.Sensor_right_front_ground = new System.Windows.Forms.Button();
            this.label18 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.Sensor_left_front_ground = new System.Windows.Forms.Button();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.groupBox12 = new System.Windows.Forms.GroupBox();
            this.listView_ActionList = new System.Windows.Forms.ListView();
            this.FileName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.btn_ActionList_play = new System.Windows.Forms.Button();
            this.btn_ActionList_refresh = new System.Windows.Forms.Button();
            this.groupBox14 = new System.Windows.Forms.GroupBox();
            this.btn_chooseActionListFolder = new System.Windows.Forms.Button();
            this.textBox_ActionListFolder = new System.Windows.Forms.TextBox();
            this.btn_V = new System.Windows.Forms.Button();
            this.label26 = new System.Windows.Forms.Label();
            this.label30 = new System.Windows.Forms.Label();
            this.label31 = new System.Windows.Forms.Label();
            this.label32 = new System.Windows.Forms.Label();
            this.label33 = new System.Windows.Forms.Label();
            this.label34 = new System.Windows.Forms.Label();
            this.label35 = new System.Windows.Forms.Label();
            this.label36 = new System.Windows.Forms.Label();
            this.label37 = new System.Windows.Forms.Label();
            this.label38 = new System.Windows.Forms.Label();
            this.groupBox_connect.SuspendLayout();
            this.groupBox_control.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_rotateArm)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_cargo)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_3rdArm)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_2ndArm)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_1stArm)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_hand)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox13.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.groupBox10.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox12.SuspendLayout();
            this.groupBox14.SuspendLayout();
            this.SuspendLayout();
            // 
            // btn_open
            // 
            this.btn_open.Location = new System.Drawing.Point(32, 210);
            this.btn_open.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_open.Name = "btn_open";
            this.btn_open.Size = new System.Drawing.Size(139, 80);
            this.btn_open.TabIndex = 5;
            this.btn_open.TabStop = false;
            this.btn_open.Text = "Open";
            this.btn_open.UseVisualStyleBackColor = true;
            this.btn_open.Click += new System.EventHandler(this.btn_open_Click);
            // 
            // groupBox_connect
            // 
            this.groupBox_connect.Controls.Add(this.button_connection_refresh);
            this.groupBox_connect.Controls.Add(this.label1);
            this.groupBox_connect.Controls.Add(this.comboBox_port);
            this.groupBox_connect.Controls.Add(this.btn_close);
            this.groupBox_connect.Controls.Add(this.btn_open);
            this.groupBox_connect.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox_connect.Location = new System.Drawing.Point(43, 52);
            this.groupBox_connect.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox_connect.Name = "groupBox_connect";
            this.groupBox_connect.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox_connect.Size = new System.Drawing.Size(568, 322);
            this.groupBox_connect.TabIndex = 6;
            this.groupBox_connect.TabStop = false;
            this.groupBox_connect.Text = "Bluetooth Connection";
            // 
            // button_connection_refresh
            // 
            this.button_connection_refresh.Location = new System.Drawing.Point(373, 210);
            this.button_connection_refresh.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.button_connection_refresh.Name = "button_connection_refresh";
            this.button_connection_refresh.Size = new System.Drawing.Size(165, 80);
            this.button_connection_refresh.TabIndex = 9;
            this.button_connection_refresh.TabStop = false;
            this.button_connection_refresh.Text = "Refresh";
            this.button_connection_refresh.UseVisualStyleBackColor = true;
            this.button_connection_refresh.Click += new System.EventHandler(this.button_connection_refresh_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 62);
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
            this.comboBox_port.Location = new System.Drawing.Point(32, 128);
            this.comboBox_port.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.comboBox_port.Name = "comboBox_port";
            this.comboBox_port.Size = new System.Drawing.Size(505, 46);
            this.comboBox_port.Sorted = true;
            this.comboBox_port.TabIndex = 7;
            this.comboBox_port.TabStop = false;
            // 
            // btn_close
            // 
            this.btn_close.Enabled = false;
            this.btn_close.Location = new System.Drawing.Point(203, 210);
            this.btn_close.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_close.Name = "btn_close";
            this.btn_close.Size = new System.Drawing.Size(139, 80);
            this.btn_close.TabIndex = 6;
            this.btn_close.TabStop = false;
            this.btn_close.Text = "Close";
            this.btn_close.UseVisualStyleBackColor = true;
            this.btn_close.Click += new System.EventHandler(this.btn_close_Click);
            // 
            // btn_A
            // 
            this.btn_A.BackColor = System.Drawing.Color.Black;
            this.btn_A.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_A.ForeColor = System.Drawing.Color.White;
            this.btn_A.Location = new System.Drawing.Point(203, 190);
            this.btn_A.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_A.Name = "btn_A";
            this.btn_A.Size = new System.Drawing.Size(96, 90);
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
            this.btn_W.Location = new System.Drawing.Point(331, 77);
            this.btn_W.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_W.Name = "btn_W";
            this.btn_W.Size = new System.Drawing.Size(96, 90);
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
            this.btn_S.Location = new System.Drawing.Point(331, 303);
            this.btn_S.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_S.Name = "btn_S";
            this.btn_S.Size = new System.Drawing.Size(96, 90);
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
            this.btn_D.Location = new System.Drawing.Point(459, 190);
            this.btn_D.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_D.Name = "btn_D";
            this.btn_D.Size = new System.Drawing.Size(96, 90);
            this.btn_D.TabIndex = 22;
            this.btn_D.TabStop = false;
            this.btn_D.Text = "D";
            this.btn_D.UseVisualStyleBackColor = false;
            // 
            // groupBox_control
            // 
            this.groupBox_control.Controls.Add(this.label38);
            this.groupBox_control.Controls.Add(this.label37);
            this.groupBox_control.Controls.Add(this.label36);
            this.groupBox_control.Controls.Add(this.label35);
            this.groupBox_control.Controls.Add(this.label34);
            this.groupBox_control.Controls.Add(this.label33);
            this.groupBox_control.Controls.Add(this.label32);
            this.groupBox_control.Controls.Add(this.label31);
            this.groupBox_control.Controls.Add(this.label30);
            this.groupBox_control.Controls.Add(this.label26);
            this.groupBox_control.Controls.Add(this.btn_V);
            this.groupBox_control.Controls.Add(this.btn_R);
            this.groupBox_control.Controls.Add(this.btn_Z);
            this.groupBox_control.Controls.Add(this.btn_C);
            this.groupBox_control.Controls.Add(this.btn_Q);
            this.groupBox_control.Controls.Add(this.btn_E);
            this.groupBox_control.Controls.Add(this.btn_D);
            this.groupBox_control.Controls.Add(this.btn_S);
            this.groupBox_control.Controls.Add(this.btn_W);
            this.groupBox_control.Controls.Add(this.btn_A);
            this.groupBox_control.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox_control.Location = new System.Drawing.Point(43, 1258);
            this.groupBox_control.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox_control.Name = "groupBox_control";
            this.groupBox_control.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox_control.Size = new System.Drawing.Size(1065, 428);
            this.groupBox_control.TabIndex = 31;
            this.groupBox_control.TabStop = false;
            this.groupBox_control.Text = "Keyboard";
            // 
            // btn_R
            // 
            this.btn_R.BackColor = System.Drawing.Color.Black;
            this.btn_R.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_R.ForeColor = System.Drawing.Color.White;
            this.btn_R.Location = new System.Drawing.Point(718, 77);
            this.btn_R.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_R.Name = "btn_R";
            this.btn_R.Size = new System.Drawing.Size(96, 90);
            this.btn_R.TabIndex = 36;
            this.btn_R.TabStop = false;
            this.btn_R.Text = "R";
            this.btn_R.UseVisualStyleBackColor = false;
            // 
            // btn_Z
            // 
            this.btn_Z.BackColor = System.Drawing.Color.Black;
            this.btn_Z.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_Z.ForeColor = System.Drawing.Color.White;
            this.btn_Z.Location = new System.Drawing.Point(203, 303);
            this.btn_Z.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_Z.Name = "btn_Z";
            this.btn_Z.Size = new System.Drawing.Size(96, 90);
            this.btn_Z.TabIndex = 35;
            this.btn_Z.TabStop = false;
            this.btn_Z.Text = "Z";
            this.btn_Z.UseVisualStyleBackColor = false;
            // 
            // btn_C
            // 
            this.btn_C.BackColor = System.Drawing.Color.Black;
            this.btn_C.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_C.ForeColor = System.Drawing.Color.White;
            this.btn_C.Location = new System.Drawing.Point(459, 303);
            this.btn_C.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_C.Name = "btn_C";
            this.btn_C.Size = new System.Drawing.Size(96, 90);
            this.btn_C.TabIndex = 34;
            this.btn_C.TabStop = false;
            this.btn_C.Text = "C";
            this.btn_C.UseVisualStyleBackColor = false;
            // 
            // btn_Q
            // 
            this.btn_Q.BackColor = System.Drawing.Color.Black;
            this.btn_Q.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_Q.ForeColor = System.Drawing.Color.White;
            this.btn_Q.Location = new System.Drawing.Point(203, 77);
            this.btn_Q.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_Q.Name = "btn_Q";
            this.btn_Q.Size = new System.Drawing.Size(96, 90);
            this.btn_Q.TabIndex = 32;
            this.btn_Q.TabStop = false;
            this.btn_Q.Text = "Q";
            this.btn_Q.UseVisualStyleBackColor = false;
            // 
            // btn_E
            // 
            this.btn_E.BackColor = System.Drawing.Color.Black;
            this.btn_E.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_E.ForeColor = System.Drawing.Color.White;
            this.btn_E.Location = new System.Drawing.Point(459, 77);
            this.btn_E.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_E.Name = "btn_E";
            this.btn_E.Size = new System.Drawing.Size(96, 90);
            this.btn_E.TabIndex = 31;
            this.btn_E.TabStop = false;
            this.btn_E.Text = "E";
            this.btn_E.UseVisualStyleBackColor = false;
            // 
            // trackBar_rotateArm
            // 
            this.trackBar_rotateArm.AutoSize = false;
            this.trackBar_rotateArm.Location = new System.Drawing.Point(200, 172);
            this.trackBar_rotateArm.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.trackBar_rotateArm.Maximum = 90;
            this.trackBar_rotateArm.Minimum = -90;
            this.trackBar_rotateArm.Name = "trackBar_rotateArm";
            this.trackBar_rotateArm.Size = new System.Drawing.Size(488, 60);
            this.trackBar_rotateArm.TabIndex = 32;
            this.trackBar_rotateArm.TabStop = false;
            this.trackBar_rotateArm.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBar_rotateArm.Scroll += new System.EventHandler(this.trackBar_rotateArm_Scroll);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label2.Location = new System.Drawing.Point(13, 182);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(165, 38);
            this.label2.TabIndex = 33;
            this.label2.Text = "rotate arm";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label3.Location = new System.Drawing.Point(56, 295);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(122, 38);
            this.label3.TabIndex = 34;
            this.label3.Text = "1st arm";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label4.Location = new System.Drawing.Point(43, 398);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(134, 38);
            this.label4.TabIndex = 35;
            this.label4.Text = "2nd arm";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label5.Location = new System.Drawing.Point(51, 510);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(127, 38);
            this.label5.TabIndex = 36;
            this.label5.Text = "3rd arm";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label6.Location = new System.Drawing.Point(88, 625);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(88, 38);
            this.label6.TabIndex = 37;
            this.label6.Text = "hand";
            // 
            // textBox_rotateArm
            // 
            this.textBox_rotateArm.Location = new System.Drawing.Point(720, 180);
            this.textBox_rotateArm.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_rotateArm.Name = "textBox_rotateArm";
            this.textBox_rotateArm.ReadOnly = true;
            this.textBox_rotateArm.Size = new System.Drawing.Size(79, 47);
            this.textBox_rotateArm.TabIndex = 38;
            this.textBox_rotateArm.TabStop = false;
            this.textBox_rotateArm.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBox_cargo);
            this.groupBox1.Controls.Add(this.trackBar_cargo);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.textBox_hand);
            this.groupBox1.Controls.Add(this.textBox_3rdArm);
            this.groupBox1.Controls.Add(this.textBox_2ndArm);
            this.groupBox1.Controls.Add(this.textBox_1stArm);
            this.groupBox1.Controls.Add(this.trackBar_3rdArm);
            this.groupBox1.Controls.Add(this.trackBar_2ndArm);
            this.groupBox1.Controls.Add(this.trackBar_1stArm);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.textBox_rotateArm);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.trackBar_rotateArm);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.trackBar_hand);
            this.groupBox1.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox1.Location = new System.Drawing.Point(645, 52);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Size = new System.Drawing.Size(837, 712);
            this.groupBox1.TabIndex = 39;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Arm Control";
            // 
            // textBox_cargo
            // 
            this.textBox_cargo.Location = new System.Drawing.Point(720, 70);
            this.textBox_cargo.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_cargo.Name = "textBox_cargo";
            this.textBox_cargo.ReadOnly = true;
            this.textBox_cargo.Size = new System.Drawing.Size(79, 47);
            this.textBox_cargo.TabIndex = 49;
            this.textBox_cargo.TabStop = false;
            this.textBox_cargo.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // trackBar_cargo
            // 
            this.trackBar_cargo.AutoSize = false;
            this.trackBar_cargo.Location = new System.Drawing.Point(200, 62);
            this.trackBar_cargo.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.trackBar_cargo.Maximum = 0;
            this.trackBar_cargo.Minimum = -90;
            this.trackBar_cargo.Name = "trackBar_cargo";
            this.trackBar_cargo.Size = new System.Drawing.Size(488, 60);
            this.trackBar_cargo.TabIndex = 48;
            this.trackBar_cargo.TabStop = false;
            this.trackBar_cargo.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBar_cargo.Scroll += new System.EventHandler(this.trackBar_cargo_Scroll);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.label7.Location = new System.Drawing.Point(80, 72);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(97, 38);
            this.label7.TabIndex = 47;
            this.label7.Text = "cargo";
            // 
            // textBox_hand
            // 
            this.textBox_hand.Location = new System.Drawing.Point(720, 622);
            this.textBox_hand.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_hand.Name = "textBox_hand";
            this.textBox_hand.ReadOnly = true;
            this.textBox_hand.Size = new System.Drawing.Size(79, 47);
            this.textBox_hand.TabIndex = 46;
            this.textBox_hand.TabStop = false;
            this.textBox_hand.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox_3rdArm
            // 
            this.textBox_3rdArm.Location = new System.Drawing.Point(720, 505);
            this.textBox_3rdArm.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_3rdArm.Name = "textBox_3rdArm";
            this.textBox_3rdArm.ReadOnly = true;
            this.textBox_3rdArm.Size = new System.Drawing.Size(79, 47);
            this.textBox_3rdArm.TabIndex = 45;
            this.textBox_3rdArm.TabStop = false;
            this.textBox_3rdArm.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox_2ndArm
            // 
            this.textBox_2ndArm.Location = new System.Drawing.Point(720, 392);
            this.textBox_2ndArm.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_2ndArm.Name = "textBox_2ndArm";
            this.textBox_2ndArm.ReadOnly = true;
            this.textBox_2ndArm.Size = new System.Drawing.Size(79, 47);
            this.textBox_2ndArm.TabIndex = 44;
            this.textBox_2ndArm.TabStop = false;
            this.textBox_2ndArm.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // textBox_1stArm
            // 
            this.textBox_1stArm.Location = new System.Drawing.Point(720, 290);
            this.textBox_1stArm.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_1stArm.Name = "textBox_1stArm";
            this.textBox_1stArm.ReadOnly = true;
            this.textBox_1stArm.Size = new System.Drawing.Size(79, 47);
            this.textBox_1stArm.TabIndex = 43;
            this.textBox_1stArm.TabStop = false;
            this.textBox_1stArm.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // trackBar_3rdArm
            // 
            this.trackBar_3rdArm.AutoSize = false;
            this.trackBar_3rdArm.Location = new System.Drawing.Point(200, 502);
            this.trackBar_3rdArm.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.trackBar_3rdArm.Maximum = 60;
            this.trackBar_3rdArm.Minimum = -60;
            this.trackBar_3rdArm.Name = "trackBar_3rdArm";
            this.trackBar_3rdArm.Size = new System.Drawing.Size(488, 60);
            this.trackBar_3rdArm.TabIndex = 41;
            this.trackBar_3rdArm.TabStop = false;
            this.trackBar_3rdArm.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBar_3rdArm.Scroll += new System.EventHandler(this.trackBar_3rdArm_Scroll);
            // 
            // trackBar_2ndArm
            // 
            this.trackBar_2ndArm.AutoSize = false;
            this.trackBar_2ndArm.Location = new System.Drawing.Point(200, 392);
            this.trackBar_2ndArm.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.trackBar_2ndArm.Maximum = 60;
            this.trackBar_2ndArm.Name = "trackBar_2ndArm";
            this.trackBar_2ndArm.Size = new System.Drawing.Size(488, 60);
            this.trackBar_2ndArm.TabIndex = 40;
            this.trackBar_2ndArm.TabStop = false;
            this.trackBar_2ndArm.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBar_2ndArm.Scroll += new System.EventHandler(this.trackBar_2ndArm_Scroll);
            // 
            // trackBar_1stArm
            // 
            this.trackBar_1stArm.AutoSize = false;
            this.trackBar_1stArm.Location = new System.Drawing.Point(200, 282);
            this.trackBar_1stArm.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.trackBar_1stArm.Maximum = 90;
            this.trackBar_1stArm.Name = "trackBar_1stArm";
            this.trackBar_1stArm.Size = new System.Drawing.Size(488, 60);
            this.trackBar_1stArm.TabIndex = 39;
            this.trackBar_1stArm.TabStop = false;
            this.trackBar_1stArm.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBar_1stArm.Value = 90;
            this.trackBar_1stArm.Scroll += new System.EventHandler(this.trackBar_1stArm_Scroll);
            // 
            // trackBar_hand
            // 
            this.trackBar_hand.AutoSize = false;
            this.trackBar_hand.Location = new System.Drawing.Point(200, 612);
            this.trackBar_hand.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.trackBar_hand.Maximum = 90;
            this.trackBar_hand.Name = "trackBar_hand";
            this.trackBar_hand.Size = new System.Drawing.Size(488, 60);
            this.trackBar_hand.TabIndex = 42;
            this.trackBar_hand.TabStop = false;
            this.trackBar_hand.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBar_hand.Scroll += new System.EventHandler(this.trackBar_hand_Scroll);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.glControl_sideView);
            this.groupBox2.Controls.Add(this.glControl_topView);
            this.groupBox2.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox2.Location = new System.Drawing.Point(1509, 52);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox2.Size = new System.Drawing.Size(1861, 712);
            this.groupBox2.TabIndex = 40;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Graphic";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.BackColor = System.Drawing.SystemColors.Control;
            this.label9.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.label9.Location = new System.Drawing.Point(987, 85);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(148, 38);
            this.label9.TabIndex = 45;
            this.label9.Text = "Top View";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.BackColor = System.Drawing.SystemColors.Control;
            this.label8.ForeColor = System.Drawing.SystemColors.MenuHighlight;
            this.label8.Location = new System.Drawing.Point(67, 85);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(154, 38);
            this.label8.TabIndex = 44;
            this.label8.Text = "Side View";
            // 
            // glControl_sideView
            // 
            this.glControl_sideView.BackColor = System.Drawing.Color.Black;
            this.glControl_sideView.Location = new System.Drawing.Point(40, 50);
            this.glControl_sideView.Margin = new System.Windows.Forms.Padding(8, 10, 8, 10);
            this.glControl_sideView.Name = "glControl_sideView";
            this.glControl_sideView.Size = new System.Drawing.Size(877, 635);
            this.glControl_sideView.TabIndex = 42;
            this.glControl_sideView.VSync = false;
            this.glControl_sideView.Load += new System.EventHandler(this.glControl_sideView_Load);
            this.glControl_sideView.Paint += new System.Windows.Forms.PaintEventHandler(this.glControl_sideView_Paint);
            this.glControl_sideView.Resize += new System.EventHandler(this.glControl_sideView_Resize);
            // 
            // glControl_topView
            // 
            this.glControl_topView.BackColor = System.Drawing.Color.Black;
            this.glControl_topView.Location = new System.Drawing.Point(949, 50);
            this.glControl_topView.Margin = new System.Windows.Forms.Padding(11, 10, 11, 10);
            this.glControl_topView.Name = "glControl_topView";
            this.glControl_topView.Size = new System.Drawing.Size(877, 635);
            this.glControl_topView.TabIndex = 43;
            this.glControl_topView.VSync = false;
            this.glControl_topView.Load += new System.EventHandler(this.glControl_topView_Load);
            this.glControl_topView.Paint += new System.Windows.Forms.PaintEventHandler(this.glControl_topView_Paint);
            this.glControl_topView.Resize += new System.EventHandler(this.glControl_topView_Resize);
            // 
            // Sensor_right_behind_behind
            // 
            this.Sensor_right_behind_behind.BackColor = System.Drawing.Color.Green;
            this.Sensor_right_behind_behind.Enabled = false;
            this.Sensor_right_behind_behind.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_right_behind_behind.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_right_behind_behind.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Sensor_right_behind_behind.Location = new System.Drawing.Point(125, 180);
            this.Sensor_right_behind_behind.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_right_behind_behind.Name = "Sensor_right_behind_behind";
            this.Sensor_right_behind_behind.Size = new System.Drawing.Size(69, 45);
            this.Sensor_right_behind_behind.TabIndex = 6;
            this.Sensor_right_behind_behind.TabStop = false;
            this.Sensor_right_behind_behind.UseVisualStyleBackColor = false;
            // 
            // Sensor_left_behind_behind
            // 
            this.Sensor_left_behind_behind.BackColor = System.Drawing.Color.Green;
            this.Sensor_left_behind_behind.Enabled = false;
            this.Sensor_left_behind_behind.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_left_behind_behind.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_left_behind_behind.Location = new System.Drawing.Point(104, 180);
            this.Sensor_left_behind_behind.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_left_behind_behind.Name = "Sensor_left_behind_behind";
            this.Sensor_left_behind_behind.Size = new System.Drawing.Size(69, 45);
            this.Sensor_left_behind_behind.TabIndex = 5;
            this.Sensor_left_behind_behind.TabStop = false;
            this.Sensor_left_behind_behind.UseVisualStyleBackColor = false;
            // 
            // Sensor_left_front_front
            // 
            this.Sensor_left_front_front.BackColor = System.Drawing.Color.Green;
            this.Sensor_left_front_front.Enabled = false;
            this.Sensor_left_front_front.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_left_front_front.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_left_front_front.Location = new System.Drawing.Point(104, 182);
            this.Sensor_left_front_front.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_left_front_front.Name = "Sensor_left_front_front";
            this.Sensor_left_front_front.Size = new System.Drawing.Size(69, 45);
            this.Sensor_left_front_front.TabIndex = 4;
            this.Sensor_left_front_front.TabStop = false;
            this.Sensor_left_front_front.UseVisualStyleBackColor = false;
            // 
            // Sensor_right_front_front
            // 
            this.Sensor_right_front_front.BackColor = System.Drawing.Color.Green;
            this.Sensor_right_front_front.Enabled = false;
            this.Sensor_right_front_front.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_right_front_front.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_right_front_front.Location = new System.Drawing.Point(119, 183);
            this.Sensor_right_front_front.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_right_front_front.Name = "Sensor_right_front_front";
            this.Sensor_right_front_front.Size = new System.Drawing.Size(69, 45);
            this.Sensor_right_front_front.TabIndex = 3;
            this.Sensor_right_front_front.UseVisualStyleBackColor = false;
            // 
            // Sensor_left_front_left
            // 
            this.Sensor_left_front_left.BackColor = System.Drawing.Color.Green;
            this.Sensor_left_front_left.Enabled = false;
            this.Sensor_left_front_left.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_left_front_left.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_left_front_left.Location = new System.Drawing.Point(104, 127);
            this.Sensor_left_front_left.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_left_front_left.Name = "Sensor_left_front_left";
            this.Sensor_left_front_left.Size = new System.Drawing.Size(69, 45);
            this.Sensor_left_front_left.TabIndex = 1;
            this.Sensor_left_front_left.TabStop = false;
            this.Sensor_left_front_left.UseVisualStyleBackColor = false;
            // 
            // Sensor_right_front_right
            // 
            this.Sensor_right_front_right.BackColor = System.Drawing.Color.Green;
            this.Sensor_right_front_right.Enabled = false;
            this.Sensor_right_front_right.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_right_front_right.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_right_front_right.Location = new System.Drawing.Point(119, 123);
            this.Sensor_right_front_right.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_right_front_right.Name = "Sensor_right_front_right";
            this.Sensor_right_front_right.Size = new System.Drawing.Size(69, 45);
            this.Sensor_right_front_right.TabIndex = 2;
            this.Sensor_right_front_right.TabStop = false;
            this.Sensor_right_front_right.UseVisualStyleBackColor = false;
            // 
            // btn_ResetArm
            // 
            this.btn_ResetArm.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_ResetArm.Location = new System.Drawing.Point(357, 398);
            this.btn_ResetArm.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_ResetArm.Name = "btn_ResetArm";
            this.btn_ResetArm.Size = new System.Drawing.Size(224, 80);
            this.btn_ResetArm.TabIndex = 10;
            this.btn_ResetArm.TabStop = false;
            this.btn_ResetArm.Text = "Reset Arm";
            this.btn_ResetArm.UseVisualStyleBackColor = true;
            this.btn_ResetArm.Click += new System.EventHandler(this.btn_ResetArm_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.groupBox6);
            this.groupBox3.Controls.Add(this.groupBox5);
            this.groupBox3.Controls.Add(this.groupBox4);
            this.groupBox3.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox3.Location = new System.Drawing.Point(43, 802);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox3.Size = new System.Drawing.Size(1803, 428);
            this.groupBox3.TabIndex = 41;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Save Data";
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.btn_delete);
            this.groupBox6.Controls.Add(this.btn_Create);
            this.groupBox6.Controls.Add(this.btn_choseSaveFile);
            this.groupBox6.Controls.Add(this.textBox_createFileName);
            this.groupBox6.Controls.Add(this.label12);
            this.groupBox6.Controls.Add(this.label11);
            this.groupBox6.Location = new System.Drawing.Point(56, 45);
            this.groupBox6.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox6.Size = new System.Drawing.Size(635, 360);
            this.groupBox6.TabIndex = 15;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "File";
            // 
            // btn_delete
            // 
            this.btn_delete.Location = new System.Drawing.Point(35, 212);
            this.btn_delete.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_delete.Name = "btn_delete";
            this.btn_delete.Size = new System.Drawing.Size(165, 100);
            this.btn_delete.TabIndex = 11;
            this.btn_delete.TabStop = false;
            this.btn_delete.Text = "Delete";
            this.btn_delete.UseVisualStyleBackColor = true;
            this.btn_delete.Click += new System.EventHandler(this.btn_delete_Click_1);
            // 
            // btn_Create
            // 
            this.btn_Create.Location = new System.Drawing.Point(35, 65);
            this.btn_Create.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_Create.Name = "btn_Create";
            this.btn_Create.Size = new System.Drawing.Size(165, 100);
            this.btn_Create.TabIndex = 7;
            this.btn_Create.TabStop = false;
            this.btn_Create.Text = "Create";
            this.btn_Create.UseVisualStyleBackColor = true;
            this.btn_Create.Click += new System.EventHandler(this.btn_Create_Click);
            // 
            // btn_choseSaveFile
            // 
            this.btn_choseSaveFile.Location = new System.Drawing.Point(235, 212);
            this.btn_choseSaveFile.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_choseSaveFile.Name = "btn_choseSaveFile";
            this.btn_choseSaveFile.Size = new System.Drawing.Size(368, 100);
            this.btn_choseSaveFile.TabIndex = 0;
            this.btn_choseSaveFile.TabStop = false;
            this.btn_choseSaveFile.Text = "Choose";
            this.btn_choseSaveFile.UseVisualStyleBackColor = true;
            this.btn_choseSaveFile.Click += new System.EventHandler(this.btn_choseFile_Click);
            // 
            // textBox_createFileName
            // 
            this.textBox_createFileName.Location = new System.Drawing.Point(291, 122);
            this.textBox_createFileName.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_createFileName.Name = "textBox_createFileName";
            this.textBox_createFileName.Size = new System.Drawing.Size(236, 47);
            this.textBox_createFileName.TabIndex = 8;
            this.textBox_createFileName.TabStop = false;
            this.textBox_createFileName.Leave += new System.EventHandler(this.textBox_createFileName_Leave);
            this.textBox_createFileName.MouseDown += new System.Windows.Forms.MouseEventHandler(this.textBox_createFileName_MouseDown);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(533, 128);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(68, 38);
            this.label12.TabIndex = 10;
            this.label12.Text = ".csv";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(227, 65);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(158, 38);
            this.label11.TabIndex = 9;
            this.label11.Text = "FileName:";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.btn_saveData);
            this.groupBox5.Controls.Add(this.btn_delData);
            this.groupBox5.Location = new System.Drawing.Point(723, 45);
            this.groupBox5.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox5.Size = new System.Drawing.Size(259, 360);
            this.groupBox5.TabIndex = 14;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "single Data";
            // 
            // btn_saveData
            // 
            this.btn_saveData.Location = new System.Drawing.Point(45, 88);
            this.btn_saveData.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_saveData.Name = "btn_saveData";
            this.btn_saveData.Size = new System.Drawing.Size(165, 100);
            this.btn_saveData.TabIndex = 2;
            this.btn_saveData.TabStop = false;
            this.btn_saveData.Text = "Save";
            this.btn_saveData.UseVisualStyleBackColor = true;
            this.btn_saveData.Click += new System.EventHandler(this.btn_save_Click);
            // 
            // btn_delData
            // 
            this.btn_delData.Location = new System.Drawing.Point(45, 235);
            this.btn_delData.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_delData.Name = "btn_delData";
            this.btn_delData.Size = new System.Drawing.Size(165, 100);
            this.btn_delData.TabIndex = 3;
            this.btn_delData.TabStop = false;
            this.btn_delData.Text = "Delete";
            this.btn_delData.UseVisualStyleBackColor = true;
            this.btn_delData.Click += new System.EventHandler(this.btn_delete_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.textBox_FileName);
            this.groupBox4.Controls.Add(this.label14);
            this.groupBox4.Controls.Add(this.label13);
            this.groupBox4.Controls.Add(this.textBox_FilePath);
            this.groupBox4.Controls.Add(this.label10);
            this.groupBox4.Controls.Add(this.textBox_data_num);
            this.groupBox4.Location = new System.Drawing.Point(1016, 45);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox4.Size = new System.Drawing.Size(757, 360);
            this.groupBox4.TabIndex = 13;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "File Info";
            // 
            // textBox_FileName
            // 
            this.textBox_FileName.Location = new System.Drawing.Point(219, 188);
            this.textBox_FileName.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_FileName.Name = "textBox_FileName";
            this.textBox_FileName.ReadOnly = true;
            this.textBox_FileName.Size = new System.Drawing.Size(511, 47);
            this.textBox_FileName.TabIndex = 14;
            this.textBox_FileName.TabStop = false;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(48, 88);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(144, 38);
            this.label14.TabIndex = 13;
            this.label14.Text = "File Path:";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(24, 190);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(166, 38);
            this.label13.TabIndex = 11;
            this.label13.Text = "File Name:";
            // 
            // textBox_FilePath
            // 
            this.textBox_FilePath.Location = new System.Drawing.Point(219, 55);
            this.textBox_FilePath.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_FilePath.Multiline = true;
            this.textBox_FilePath.Name = "textBox_FilePath";
            this.textBox_FilePath.ReadOnly = true;
            this.textBox_FilePath.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox_FilePath.Size = new System.Drawing.Size(511, 99);
            this.textBox_FilePath.TabIndex = 12;
            this.textBox_FilePath.TabStop = false;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(19, 278);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(173, 38);
            this.label10.TabIndex = 6;
            this.label10.Text = "Data_Num:";
            // 
            // textBox_data_num
            // 
            this.textBox_data_num.Location = new System.Drawing.Point(219, 275);
            this.textBox_data_num.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_data_num.Name = "textBox_data_num";
            this.textBox_data_num.ReadOnly = true;
            this.textBox_data_num.Size = new System.Drawing.Size(132, 47);
            this.textBox_data_num.TabIndex = 5;
            this.textBox_data_num.TabStop = false;
            this.textBox_data_num.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.groupBox13);
            this.groupBox7.Controls.Add(this.groupBox11);
            this.groupBox7.Controls.Add(this.groupBox10);
            this.groupBox7.Controls.Add(this.groupBox9);
            this.groupBox7.Controls.Add(this.groupBox8);
            this.groupBox7.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox7.Location = new System.Drawing.Point(2832, 802);
            this.groupBox7.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox7.Size = new System.Drawing.Size(539, 872);
            this.groupBox7.TabIndex = 42;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Sensor";
            // 
            // groupBox13
            // 
            this.groupBox13.Controls.Add(this.Example_Red);
            this.groupBox13.Controls.Add(this.label25);
            this.groupBox13.Controls.Add(this.label24);
            this.groupBox13.Controls.Add(this.Example_Green);
            this.groupBox13.Location = new System.Drawing.Point(51, 85);
            this.groupBox13.Name = "groupBox13";
            this.groupBox13.Size = new System.Drawing.Size(444, 150);
            this.groupBox13.TabIndex = 44;
            this.groupBox13.TabStop = false;
            this.groupBox13.Text = "資料展示";
            // 
            // Example_Red
            // 
            this.Example_Red.BackColor = System.Drawing.Color.Red;
            this.Example_Red.Enabled = false;
            this.Example_Red.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Example_Red.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Example_Red.Location = new System.Drawing.Point(355, 74);
            this.Example_Red.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Example_Red.Name = "Example_Red";
            this.Example_Red.Size = new System.Drawing.Size(69, 45);
            this.Example_Red.TabIndex = 46;
            this.Example_Red.TabStop = false;
            this.Example_Red.UseVisualStyleBackColor = false;
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(290, 79);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(47, 38);
            this.label25.TabIndex = 47;
            this.label25.Text = "有";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(51, 76);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(47, 38);
            this.label24.TabIndex = 5;
            this.label24.Text = "無";
            // 
            // Example_Green
            // 
            this.Example_Green.BackColor = System.Drawing.Color.Green;
            this.Example_Green.Enabled = false;
            this.Example_Green.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Example_Green.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Example_Green.Location = new System.Drawing.Point(104, 74);
            this.Example_Green.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Example_Green.Name = "Example_Green";
            this.Example_Green.Size = new System.Drawing.Size(69, 45);
            this.Example_Green.TabIndex = 5;
            this.Example_Green.TabStop = false;
            this.Example_Green.UseVisualStyleBackColor = false;
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.Sensor_right_behind_ground);
            this.groupBox11.Controls.Add(this.Sensor_right_behind_right);
            this.groupBox11.Controls.Add(this.label27);
            this.groupBox11.Controls.Add(this.label28);
            this.groupBox11.Controls.Add(this.label29);
            this.groupBox11.Controls.Add(this.Sensor_right_behind_behind);
            this.groupBox11.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox11.Location = new System.Drawing.Point(287, 579);
            this.groupBox11.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox11.Size = new System.Drawing.Size(208, 252);
            this.groupBox11.TabIndex = 45;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "右後";
            // 
            // Sensor_right_behind_ground
            // 
            this.Sensor_right_behind_ground.BackColor = System.Drawing.Color.Green;
            this.Sensor_right_behind_ground.Enabled = false;
            this.Sensor_right_behind_ground.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_right_behind_ground.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_right_behind_ground.Location = new System.Drawing.Point(125, 65);
            this.Sensor_right_behind_ground.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_right_behind_ground.Name = "Sensor_right_behind_ground";
            this.Sensor_right_behind_ground.Size = new System.Drawing.Size(69, 45);
            this.Sensor_right_behind_ground.TabIndex = 14;
            this.Sensor_right_behind_ground.TabStop = false;
            this.Sensor_right_behind_ground.UseVisualStyleBackColor = false;
            // 
            // Sensor_right_behind_right
            // 
            this.Sensor_right_behind_right.BackColor = System.Drawing.Color.Green;
            this.Sensor_right_behind_right.Enabled = false;
            this.Sensor_right_behind_right.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_right_behind_right.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_right_behind_right.Location = new System.Drawing.Point(125, 123);
            this.Sensor_right_behind_right.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_right_behind_right.Name = "Sensor_right_behind_right";
            this.Sensor_right_behind_right.Size = new System.Drawing.Size(69, 45);
            this.Sensor_right_behind_right.TabIndex = 13;
            this.Sensor_right_behind_right.TabStop = false;
            this.Sensor_right_behind_right.UseVisualStyleBackColor = false;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(24, 190);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(77, 38);
            this.label27.TabIndex = 7;
            this.label27.Text = "朝後";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(24, 68);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(77, 38);
            this.label28.TabIndex = 5;
            this.label28.Text = "朝地";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(24, 130);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(77, 38);
            this.label29.TabIndex = 6;
            this.label29.Text = "朝右";
            // 
            // groupBox10
            // 
            this.groupBox10.Controls.Add(this.Sensor_left_behind_ground);
            this.groupBox10.Controls.Add(this.Sensor_left_behind_left);
            this.groupBox10.Controls.Add(this.label21);
            this.groupBox10.Controls.Add(this.label23);
            this.groupBox10.Controls.Add(this.label22);
            this.groupBox10.Controls.Add(this.Sensor_left_behind_behind);
            this.groupBox10.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox10.Location = new System.Drawing.Point(51, 579);
            this.groupBox10.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox10.Size = new System.Drawing.Size(208, 252);
            this.groupBox10.TabIndex = 45;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "左後";
            // 
            // Sensor_left_behind_ground
            // 
            this.Sensor_left_behind_ground.BackColor = System.Drawing.Color.Green;
            this.Sensor_left_behind_ground.Enabled = false;
            this.Sensor_left_behind_ground.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_left_behind_ground.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_left_behind_ground.Location = new System.Drawing.Point(104, 60);
            this.Sensor_left_behind_ground.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_left_behind_ground.Name = "Sensor_left_behind_ground";
            this.Sensor_left_behind_ground.Size = new System.Drawing.Size(69, 45);
            this.Sensor_left_behind_ground.TabIndex = 12;
            this.Sensor_left_behind_ground.TabStop = false;
            this.Sensor_left_behind_ground.UseVisualStyleBackColor = false;
            // 
            // Sensor_left_behind_left
            // 
            this.Sensor_left_behind_left.BackColor = System.Drawing.Color.Green;
            this.Sensor_left_behind_left.Enabled = false;
            this.Sensor_left_behind_left.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_left_behind_left.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_left_behind_left.Location = new System.Drawing.Point(104, 123);
            this.Sensor_left_behind_left.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_left_behind_left.Name = "Sensor_left_behind_left";
            this.Sensor_left_behind_left.Size = new System.Drawing.Size(69, 45);
            this.Sensor_left_behind_left.TabIndex = 11;
            this.Sensor_left_behind_left.TabStop = false;
            this.Sensor_left_behind_left.UseVisualStyleBackColor = false;
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(21, 188);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(77, 38);
            this.label21.TabIndex = 10;
            this.label21.Text = "朝後";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(21, 68);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(77, 38);
            this.label23.TabIndex = 8;
            this.label23.Text = "朝地";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(21, 130);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(77, 38);
            this.label22.TabIndex = 9;
            this.label22.Text = "朝左";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.Sensor_right_front_ground);
            this.groupBox9.Controls.Add(this.label18);
            this.groupBox9.Controls.Add(this.label20);
            this.groupBox9.Controls.Add(this.label19);
            this.groupBox9.Controls.Add(this.Sensor_right_front_front);
            this.groupBox9.Controls.Add(this.Sensor_right_front_right);
            this.groupBox9.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox9.Location = new System.Drawing.Point(287, 280);
            this.groupBox9.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox9.Size = new System.Drawing.Size(208, 252);
            this.groupBox9.TabIndex = 44;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "右前";
            // 
            // Sensor_right_front_ground
            // 
            this.Sensor_right_front_ground.BackColor = System.Drawing.Color.Green;
            this.Sensor_right_front_ground.Enabled = false;
            this.Sensor_right_front_ground.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_right_front_ground.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_right_front_ground.Location = new System.Drawing.Point(119, 61);
            this.Sensor_right_front_ground.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_right_front_ground.Name = "Sensor_right_front_ground";
            this.Sensor_right_front_ground.Size = new System.Drawing.Size(69, 45);
            this.Sensor_right_front_ground.TabIndex = 6;
            this.Sensor_right_front_ground.TabStop = false;
            this.Sensor_right_front_ground.UseVisualStyleBackColor = false;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(24, 190);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(77, 38);
            this.label18.TabIndex = 7;
            this.label18.Text = "朝前";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(24, 68);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(77, 38);
            this.label20.TabIndex = 5;
            this.label20.Text = "朝地";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(24, 130);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(77, 38);
            this.label19.TabIndex = 6;
            this.label19.Text = "朝右";
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.Sensor_left_front_ground);
            this.groupBox8.Controls.Add(this.Sensor_left_front_front);
            this.groupBox8.Controls.Add(this.Sensor_left_front_left);
            this.groupBox8.Controls.Add(this.label15);
            this.groupBox8.Controls.Add(this.label16);
            this.groupBox8.Controls.Add(this.label17);
            this.groupBox8.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox8.Location = new System.Drawing.Point(51, 280);
            this.groupBox8.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox8.Size = new System.Drawing.Size(208, 252);
            this.groupBox8.TabIndex = 43;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "左前";
            // 
            // Sensor_left_front_ground
            // 
            this.Sensor_left_front_ground.BackColor = System.Drawing.Color.Green;
            this.Sensor_left_front_ground.Enabled = false;
            this.Sensor_left_front_ground.FlatAppearance.BorderColor = System.Drawing.Color.Silver;
            this.Sensor_left_front_ground.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.Sensor_left_front_ground.Location = new System.Drawing.Point(104, 60);
            this.Sensor_left_front_ground.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Sensor_left_front_ground.Name = "Sensor_left_front_ground";
            this.Sensor_left_front_ground.Size = new System.Drawing.Size(69, 45);
            this.Sensor_left_front_ground.TabIndex = 5;
            this.Sensor_left_front_ground.TabStop = false;
            this.Sensor_left_front_ground.UseVisualStyleBackColor = false;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(21, 62);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(77, 38);
            this.label15.TabIndex = 0;
            this.label15.Text = "朝地";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(21, 130);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(77, 38);
            this.label16.TabIndex = 1;
            this.label16.Text = "朝左";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(21, 195);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(77, 38);
            this.label17.TabIndex = 2;
            this.label17.Text = "朝前";
            // 
            // groupBox12
            // 
            this.groupBox12.Controls.Add(this.listView_ActionList);
            this.groupBox12.Controls.Add(this.btn_ActionList_play);
            this.groupBox12.Controls.Add(this.btn_ActionList_refresh);
            this.groupBox12.Controls.Add(this.groupBox14);
            this.groupBox12.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.groupBox12.Location = new System.Drawing.Point(1877, 802);
            this.groupBox12.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox12.Name = "groupBox12";
            this.groupBox12.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox12.Size = new System.Drawing.Size(928, 872);
            this.groupBox12.TabIndex = 43;
            this.groupBox12.TabStop = false;
            this.groupBox12.Text = "Action";
            // 
            // listView_ActionList
            // 
            this.listView_ActionList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.FileName});
            this.listView_ActionList.HideSelection = false;
            this.listView_ActionList.Location = new System.Drawing.Point(48, 320);
            this.listView_ActionList.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.listView_ActionList.Name = "listView_ActionList";
            this.listView_ActionList.Size = new System.Drawing.Size(825, 349);
            this.listView_ActionList.TabIndex = 7;
            this.listView_ActionList.TabStop = false;
            this.listView_ActionList.UseCompatibleStateImageBehavior = false;
            this.listView_ActionList.View = System.Windows.Forms.View.Details;
            // 
            // FileName
            // 
            this.FileName.Text = "FileName";
            this.FileName.Width = 300;
            // 
            // btn_ActionList_play
            // 
            this.btn_ActionList_play.Location = new System.Drawing.Point(603, 720);
            this.btn_ActionList_play.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_ActionList_play.Name = "btn_ActionList_play";
            this.btn_ActionList_play.Size = new System.Drawing.Size(165, 90);
            this.btn_ActionList_play.TabIndex = 6;
            this.btn_ActionList_play.TabStop = false;
            this.btn_ActionList_play.Text = "Play";
            this.btn_ActionList_play.UseVisualStyleBackColor = true;
            this.btn_ActionList_play.Click += new System.EventHandler(this.btn_ActionList_play_Click);
            // 
            // btn_ActionList_refresh
            // 
            this.btn_ActionList_refresh.Location = new System.Drawing.Point(144, 735);
            this.btn_ActionList_refresh.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_ActionList_refresh.Name = "btn_ActionList_refresh";
            this.btn_ActionList_refresh.Size = new System.Drawing.Size(165, 90);
            this.btn_ActionList_refresh.TabIndex = 5;
            this.btn_ActionList_refresh.TabStop = false;
            this.btn_ActionList_refresh.Text = "Refresh";
            this.btn_ActionList_refresh.UseVisualStyleBackColor = true;
            this.btn_ActionList_refresh.Click += new System.EventHandler(this.btn_ActionList_refresh_Click);
            // 
            // groupBox14
            // 
            this.groupBox14.Controls.Add(this.btn_chooseActionListFolder);
            this.groupBox14.Controls.Add(this.textBox_ActionListFolder);
            this.groupBox14.Location = new System.Drawing.Point(48, 75);
            this.groupBox14.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox14.Name = "groupBox14";
            this.groupBox14.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox14.Size = new System.Drawing.Size(824, 205);
            this.groupBox14.TabIndex = 4;
            this.groupBox14.TabStop = false;
            this.groupBox14.Text = "Folder";
            // 
            // btn_chooseActionListFolder
            // 
            this.btn_chooseActionListFolder.Location = new System.Drawing.Point(32, 72);
            this.btn_chooseActionListFolder.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_chooseActionListFolder.Name = "btn_chooseActionListFolder";
            this.btn_chooseActionListFolder.Size = new System.Drawing.Size(157, 88);
            this.btn_chooseActionListFolder.TabIndex = 1;
            this.btn_chooseActionListFolder.TabStop = false;
            this.btn_chooseActionListFolder.Text = "Choose";
            this.btn_chooseActionListFolder.UseVisualStyleBackColor = true;
            this.btn_chooseActionListFolder.Click += new System.EventHandler(this.btn_chooseActionListFolder_Click);
            // 
            // textBox_ActionListFolder
            // 
            this.textBox_ActionListFolder.Location = new System.Drawing.Point(213, 72);
            this.textBox_ActionListFolder.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.textBox_ActionListFolder.Multiline = true;
            this.textBox_ActionListFolder.Name = "textBox_ActionListFolder";
            this.textBox_ActionListFolder.ReadOnly = true;
            this.textBox_ActionListFolder.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox_ActionListFolder.Size = new System.Drawing.Size(567, 86);
            this.textBox_ActionListFolder.TabIndex = 3;
            this.textBox_ActionListFolder.TabStop = false;
            // 
            // btn_V
            // 
            this.btn_V.BackColor = System.Drawing.Color.Black;
            this.btn_V.Font = new System.Drawing.Font("微軟正黑體", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(136)));
            this.btn_V.ForeColor = System.Drawing.Color.White;
            this.btn_V.Location = new System.Drawing.Point(718, 303);
            this.btn_V.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btn_V.Name = "btn_V";
            this.btn_V.Size = new System.Drawing.Size(96, 90);
            this.btn_V.TabIndex = 39;
            this.btn_V.TabStop = false;
            this.btn_V.Text = "V";
            this.btn_V.UseVisualStyleBackColor = false;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(832, 103);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(167, 38);
            this.label26.TabIndex = 40;
            this.label26.Text = "順時針旋轉";
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(832, 331);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(167, 38);
            this.label30.TabIndex = 41;
            this.label30.Text = "逆時針旋轉";
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(590, 103);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(77, 38);
            this.label31.TabIndex = 42;
            this.label31.Text = "右前";
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(590, 216);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(77, 38);
            this.label32.TabIndex = 43;
            this.label32.Text = "向右";
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(590, 329);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(77, 38);
            this.label33.TabIndex = 44;
            this.label33.Text = "右後";
            // 
            // label34
            // 
            this.label34.AutoSize = true;
            this.label34.Location = new System.Drawing.Point(92, 103);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(77, 38);
            this.label34.TabIndex = 45;
            this.label34.Text = "左前";
            // 
            // label35
            // 
            this.label35.AutoSize = true;
            this.label35.Location = new System.Drawing.Point(92, 216);
            this.label35.Name = "label35";
            this.label35.Size = new System.Drawing.Size(77, 38);
            this.label35.TabIndex = 46;
            this.label35.Text = "向左";
            // 
            // label36
            // 
            this.label36.AutoSize = true;
            this.label36.Location = new System.Drawing.Point(92, 329);
            this.label36.Name = "label36";
            this.label36.Size = new System.Drawing.Size(77, 38);
            this.label36.TabIndex = 47;
            this.label36.Text = "左後";
            // 
            // label37
            // 
            this.label37.AutoSize = true;
            this.label37.Location = new System.Drawing.Point(342, 190);
            this.label37.Name = "label37";
            this.label37.Size = new System.Drawing.Size(77, 38);
            this.label37.TabIndex = 48;
            this.label37.Text = "向前";
            // 
            // label38
            // 
            this.label38.AutoSize = true;
            this.label38.Location = new System.Drawing.Point(342, 238);
            this.label38.Name = "label38";
            this.label38.Size = new System.Drawing.Size(77, 38);
            this.label38.TabIndex = 49;
            this.label38.Text = "向後";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(16F, 30F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(3400, 1702);
            this.Controls.Add(this.groupBox12);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.btn_ResetArm);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox_connect);
            this.Controls.Add(this.groupBox_control);
            this.KeyPreview = true;
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "ControlPanel";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyUp);
            this.groupBox_connect.ResumeLayout(false);
            this.groupBox_connect.PerformLayout();
            this.groupBox_control.ResumeLayout(false);
            this.groupBox_control.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_rotateArm)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_cargo)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_3rdArm)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_2ndArm)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_1stArm)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar_hand)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox13.ResumeLayout(false);
            this.groupBox13.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            this.groupBox10.ResumeLayout(false);
            this.groupBox10.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox12.ResumeLayout(false);
            this.groupBox14.ResumeLayout(false);
            this.groupBox14.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button btn_open;
        private System.Windows.Forms.GroupBox groupBox_connect;
        private System.Windows.Forms.Button btn_close;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_A;
        private System.Windows.Forms.Button btn_W;
        private System.Windows.Forms.Button btn_S;
        private System.Windows.Forms.Button btn_D;
        private System.Windows.Forms.GroupBox groupBox_control;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button button_connection_refresh;
        private System.Windows.Forms.ComboBox comboBox_port;
        private System.Windows.Forms.Button btn_Z;
        private System.Windows.Forms.Button btn_C;
        private System.Windows.Forms.Button btn_Q;
        private System.Windows.Forms.Button btn_E;
        private System.Windows.Forms.Button btn_R;
        private System.Windows.Forms.TrackBar trackBar_rotateArm;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBox_rotateArm;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TrackBar trackBar_hand;
        private System.Windows.Forms.TrackBar trackBar_3rdArm;
        private System.Windows.Forms.TrackBar trackBar_2ndArm;
        private System.Windows.Forms.TrackBar trackBar_1stArm;
        private System.Windows.Forms.TextBox textBox_hand;
        private System.Windows.Forms.TextBox textBox_3rdArm;
        private System.Windows.Forms.TextBox textBox_2ndArm;
        private System.Windows.Forms.TextBox textBox_1stArm;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button Sensor_right_behind_behind;
        private System.Windows.Forms.Button Sensor_left_behind_behind;
        private System.Windows.Forms.Button Sensor_left_front_front;
        private System.Windows.Forms.Button Sensor_right_front_front;
        private System.Windows.Forms.Button Sensor_right_front_right;
        private System.Windows.Forms.Button Sensor_left_front_left;
        private System.Windows.Forms.TrackBar trackBar_cargo;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBox_cargo;
        private System.Windows.Forms.Button btn_ResetArm;
        private OpenTK.GLControl glControl_sideView;
        private OpenTK.GLControl glControl_topView;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btn_delData;
        private System.Windows.Forms.Button btn_saveData;
        private System.Windows.Forms.Button btn_choseSaveFile;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBox_data_num;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBox_createFileName;
        private System.Windows.Forms.Button btn_Create;
        private System.Windows.Forms.TextBox textBox_FilePath;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox textBox_FileName;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Button btn_delete;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.GroupBox groupBox10;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.GroupBox groupBox12;
        private System.Windows.Forms.Button Example_Red;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.Button Example_Green;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.GroupBox groupBox14;
        private System.Windows.Forms.Button btn_chooseActionListFolder;
        private System.Windows.Forms.TextBox textBox_ActionListFolder;
        private System.Windows.Forms.Button btn_ActionList_refresh;
        private System.Windows.Forms.Button btn_ActionList_play;
        private System.Windows.Forms.ListView listView_ActionList;
        private System.Windows.Forms.ColumnHeader FileName;
        private System.Windows.Forms.Button Sensor_right_front_ground;
        private System.Windows.Forms.Button Sensor_left_front_ground;
        private System.Windows.Forms.Button Sensor_right_behind_ground;
        private System.Windows.Forms.Button Sensor_right_behind_right;
        private System.Windows.Forms.Button Sensor_left_behind_ground;
        private System.Windows.Forms.Button Sensor_left_behind_left;
        private System.Windows.Forms.GroupBox groupBox13;
        private System.Windows.Forms.Button btn_V;
        private System.Windows.Forms.Label label36;
        private System.Windows.Forms.Label label35;
        private System.Windows.Forms.Label label34;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label37;
        private System.Windows.Forms.Label label38;
    }
}

