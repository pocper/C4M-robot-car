using System;
using System.Drawing;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace Bluetooth
{
    public partial class Form1 : Form
    {
        //string[] myKeys = new string[] { "W", "A", "S", "D", "Q", "E", "C", "Z", "R", "Space", "ControlKey", "Up", "Down", "Left", "Right", "ShiftKey", "Return" };
        string[] myKeys = new string[] { "W", "A", "S", "D", "Q", "E", "C", "Z", "R"};
        int[] Arm_Init_Degree = new int[7] { 0, 0, 0, 0, 0, 0, 0 };
        //TODO 校正
        // - 一個是v3丟資料伺服機角度需要校正
        // - 一個是電腦資料到顯示需要校正

        // - trackBar 能校正最好

        // 想到一個校正的方法
        // 先用電腦控制到正前方校正
        // 再用電腦顯示的校正
        
        //TODO 找到原因為何車斗從-3~-60就攤平
        int[] Servo_Compensate_Degree = new int[7] { -3, -3, 0, 55, -60, 0, 0 };

        string objFilePath = "./model_Robot/";
        string[] objName = { "hand_left", "hand_right", "third_arm", "rotate_arm", "first_arm", "second_arm", "cargo", "body" };


        const int totalParts = 8;
        objLoader[] obj = new objLoader[totalParts];
        Robot robot;
        Environment environment;

        string csvFileFolder = "RotationData";
        string csvFile;
        int data_num;

        bool isEntercsvFileName = false;

        class Canvas
        {
            public Shader[] shader = new Shader[totalParts];
            public Camera camera;
        }

        Canvas sideView;
        Canvas topView;


        public Form1()
        {
            InitializeComponent();
            Init_canvas();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            RefreshComport();
            Init_textBox_value();
            update_Degree(trackBar_rotateArm.Value, trackBar_1stArm.Value, trackBar_2ndArm.Value, trackBar_3rdArm.Value, trackBar_hand.Value, trackBar_cargo.Value);
        }

        private void DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort spl = (SerialPort)sender;
            string data = spl.ReadExisting();
            serialPort1.DiscardInBuffer();

            if (data.Length == 4 && data[0] == '@' && data[2] == '@')
            {
                updateSensorColor(Convert.ToInt32(data[1]));
            }
        }

        private void updateSensorColor(int num)
        {
            string SensorData = Convert.ToString(num, 2);
            string SensorData_bin = SensorData.PadLeft(6, '0');

            if (SensorData_bin[0] == '1')
                Sensor_right.BackColor = Color.Red;
            else
                Sensor_right.BackColor = Color.Green;

            if (SensorData_bin[1] == '1')
                Sensor_right_front.BackColor = Color.Red;
            else
                Sensor_right_front.BackColor = Color.Green;

            if (SensorData_bin[2] == '1')
                Sensor_right_behind.BackColor = Color.Red;
            else
                Sensor_right_behind.BackColor = Color.Green;

            if (SensorData_bin[3] == '1')
                Sensor_left_behind.BackColor = Color.Red;
            else
                Sensor_left_behind.BackColor = Color.Green;

            if (SensorData_bin[4] == '1')
                Sensor_left_front.BackColor = Color.Red;
            else
                Sensor_left_front.BackColor = Color.Green;

            if (SensorData_bin[5] == '1')
                Sensor_left.BackColor = Color.Red;
            else
                Sensor_left.BackColor = Color.Green;
        }

        public void SendData(string str)
        {
            if (str != null && serialPort1.IsOpen)
            {
                serialPort1.DiscardOutBuffer();
                serialPort1.Write(str);
            }
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            //這樣寫有問題
            //若開啟的com port 不正常會故障
            int index = Array.IndexOf(myKeys, e.KeyCode.ToString());

            if (serialPort1.IsOpen && index > -1)
                SendData("!" + myKeys[index] + "!");


            if (e.Control)
            {
                btn_ctrl.BackColor = Color.Yellow;
                btn_ctrl.ForeColor = Color.Black;
            }

            if (e.Shift)
            {
                btn_shift.BackColor = Color.Yellow;
                btn_shift.ForeColor = Color.Black;
            }

            switch (e.KeyCode)
            {
                case Keys.W:
                    btn_W.BackColor = Color.Yellow;
                    btn_W.ForeColor = Color.Black;
                    break;

                case Keys.A:
                    btn_A.BackColor = Color.Yellow;
                    btn_A.ForeColor = Color.Black;
                    break;

                case Keys.S:
                    btn_S.BackColor = Color.Yellow;
                    btn_S.ForeColor = Color.Black;
                    break;

                case Keys.D:
                    btn_D.BackColor = Color.Yellow;
                    btn_D.ForeColor = Color.Black;
                    break;

                case Keys.Q:
                    btn_Q.BackColor = Color.Yellow;
                    btn_Q.ForeColor = Color.Black;
                    break;

                case Keys.E:
                    btn_E.BackColor = Color.Yellow;
                    btn_E.ForeColor = Color.Black;
                    break;

                case Keys.C:
                    btn_C.BackColor = Color.Yellow;
                    btn_C.ForeColor = Color.Black;
                    break;

                case Keys.Z:
                    btn_Z.BackColor = Color.Yellow;
                    btn_Z.ForeColor = Color.Black;
                    break;

                case Keys.R:
                    btn_R.BackColor = Color.Yellow;
                    btn_R.ForeColor = Color.Black;
                    break;

                case Keys.Enter:
                    btn_enter.BackColor = Color.Yellow;
                    btn_enter.ForeColor = Color.Black;
                    break;

                case Keys.Up:
                    btn_up.BackColor = Color.Yellow;
                    btn_up.ForeColor = Color.Black;
                    break;

                case Keys.Down:
                    btn_down.BackColor = Color.Yellow;
                    btn_down.ForeColor = Color.Black;
                    break;

                case Keys.Left:
                    btn_left.BackColor = Color.Yellow;
                    btn_left.ForeColor = Color.Black;
                    break;

                case Keys.Right:
                    btn_right.BackColor = Color.Yellow;
                    btn_right.ForeColor = Color.Black;
                    break;

                case Keys.Space:
                    btn_space.BackColor = Color.Yellow;
                    btn_space.ForeColor = Color.Black;
                    break;
            }

            //e.Handled = true;
            if (!isEntercsvFileName)
                label1.Focus();
            else
                textBox_createFileName.Focus();
        }

        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {
            btn_W.BackColor = Color.Black;
            btn_W.ForeColor = Color.White;

            btn_A.BackColor = Color.Black;
            btn_A.ForeColor = Color.White;

            btn_S.BackColor = Color.Black;
            btn_S.ForeColor = Color.White;

            btn_D.BackColor = Color.Black;
            btn_D.ForeColor = Color.White;

            btn_E.BackColor = Color.Black;
            btn_E.ForeColor = Color.White;

            btn_Q.BackColor = Color.Black;
            btn_Q.ForeColor = Color.White;

            btn_C.BackColor = Color.Black;
            btn_C.ForeColor = Color.White;

            btn_Z.BackColor = Color.Black;
            btn_Z.ForeColor = Color.White;

            btn_R.BackColor = Color.Black;
            btn_R.ForeColor = Color.White;

            btn_ctrl.BackColor = Color.Black;
            btn_ctrl.ForeColor = Color.White;

            btn_enter.BackColor = Color.Black;
            btn_enter.ForeColor = Color.White;

            btn_space.BackColor = Color.Black;
            btn_space.ForeColor = Color.White;

            btn_shift.BackColor = Color.Black;
            btn_shift.ForeColor = Color.White;

            btn_left.BackColor = Color.Black;
            btn_left.ForeColor = Color.White;

            btn_up.BackColor = Color.Black;
            btn_up.ForeColor = Color.White;

            btn_right.BackColor = Color.Black;
            btn_right.ForeColor = Color.White;

            btn_down.BackColor = Color.Black;
            btn_down.ForeColor = Color.White;
        }

        private void btn_open_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrEmpty(comboBox_port.Text))
            {
                serialPort1.PortName = comboBox_port.Text;
                serialPort1.BaudRate = 38400;
                serialPort1.DataBits = 8;
                serialPort1.StopBits = StopBits.One;

                try
                {
                    if (!serialPort1.IsOpen)
                    {
                        serialPort1.Open();

                        btn_open.Enabled = false;
                        btn_close.Enabled = true;

                        serialPort1.DataReceived += new SerialDataReceivedEventHandler(DataReceived);

                        timer1.Interval = 10000;
                        //timer1.Start();
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void close_comPort()
        {
            try
            {
                if (serialPort1.IsOpen)
                {
                    serialPort1.Close();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void btn_close_Click(object sender, EventArgs e)
        {
            btn_open.Enabled = true;
            btn_close.Enabled = false;

            close_comPort();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            close_comPort();
        }

        private void RefreshComport()
        {
            string[] ports = SerialPort.GetPortNames();
            comboBox_port.Items.Clear();
            comboBox_port.ResetText();
            comboBox_port.Items.AddRange(ports);

            if (ports.Length != 0)
                comboBox_port.SelectedIndex = 0;
        }

        private void button_connection_refresh_Click(object sender, EventArgs e)
        {
            RefreshComport();
        }

        private void textBox_log_TextChanged(object sender, EventArgs e)
        {
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

        }

        private void Init_textBox_value()
        {
            textBox_cargo.Text = trackBar_cargo.Value.ToString();
            textBox_rotateArm.Text = trackBar_rotateArm.Value.ToString();
            textBox_1stArm.Text = trackBar_1stArm.Value.ToString();
            textBox_2ndArm.Text = trackBar_2ndArm.Value.ToString();
            textBox_3rdArm.Text = trackBar_3rdArm.Value.ToString();
            textBox_hand.Text = trackBar_hand.Value.ToString();
        }

        private void update_Degree(int rotate_arm, int first_arm, int second_arm, int third_arm, int hand_left, int cargo)
        {
            robot.rotateDegree[robot.Idx("rotate_arm")] = -90 - rotate_arm;
            robot.rotateDegree[robot.Idx("first_arm")] = -first_arm;
            robot.rotateDegree[robot.Idx("second_arm")] = -second_arm;
            robot.rotateDegree[robot.Idx("third_arm")] = third_arm;
            robot.rotateDegree[robot.Idx("hand_left")] = hand_left;
            robot.rotateDegree[robot.Idx("hand_right")] = -hand_left;
            robot.rotateDegree[robot.Idx("cargo")] = cargo;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_rotateArm_Scroll(object sender, EventArgs e)
        {
            textBox_rotateArm.Text = trackBar_rotateArm.Value.ToString();
            SendData("#3_" + deg2Data(trackBar_rotateArm.Value + Servo_Compensate_Degree[2]) + "#");

            robot.rotateDegree[robot.Idx("rotate_arm")] = -90 - trackBar_rotateArm.Value;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();

        }

        private void trackBar_1stArm_Scroll(object sender, EventArgs e)
        {
            textBox_1stArm.Text = trackBar_1stArm.Value.ToString();
            SendData("#4_" + deg2Data(trackBar_1stArm.Value + Servo_Compensate_Degree[3]) + "#");

            robot.rotateDegree[robot.Idx("first_arm")] = -trackBar_1stArm.Value;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_2ndArm_Scroll(object sender, EventArgs e)
        {
            textBox_2ndArm.Text = trackBar_2ndArm.Value.ToString();
            SendData("#5_" + deg2Data(trackBar_2ndArm.Value + Servo_Compensate_Degree[4]) + "#");

            robot.rotateDegree[robot.Idx("second_arm")] = -trackBar_2ndArm.Value;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_3rdArm_Scroll(object sender, EventArgs e)
        {
            textBox_3rdArm.Text = trackBar_3rdArm.Value.ToString();
            SendData("#6_" + deg2Data(trackBar_3rdArm.Value + Servo_Compensate_Degree[5]) + "#");

            robot.rotateDegree[robot.Idx("third_arm")] = -trackBar_3rdArm.Value;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_hand_Scroll(object sender, EventArgs e)
        {
            textBox_hand.Text = trackBar_hand.Value.ToString();
            SendData("#7_" + deg2Data(trackBar_hand.Value + Servo_Compensate_Degree[6]) + "#");

            robot.rotateDegree[robot.Idx("hand_left")] = trackBar_hand.Value;
            robot.rotateDegree[robot.Idx("hand_right")] = -robot.rotateDegree[robot.Idx("hand_left")];

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_cargo_Scroll(object sender, EventArgs e)
        {
            textBox_cargo.Text = trackBar_cargo.Value.ToString();
            SendData("#1_" + deg2Data(trackBar_cargo.Value + Servo_Compensate_Degree[0]) + "#");

            robot.rotateDegree[robot.Idx("cargo")] = trackBar_cargo.Value;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private string deg2Data(int num)
        {
            string Data_str;

            if (num >= 0)
                Data_str = String.Format("+{0:00}", num);
            else
                Data_str = String.Format("{0:00}", num);

            return Data_str;
        }

        private void btn_ResetArm_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < Arm_Init_Degree.Length; i++)
            {
                string str = String.Format("#{0}_{1}#", i + 1, deg2Data(Arm_Init_Degree[i] + Servo_Compensate_Degree[i]));
                SendData(str);
                Thread.Sleep(50);
            }


            trackBar_cargo.Value = Arm_Init_Degree[0];
            trackBar_rotateArm.Value = Arm_Init_Degree[2];
            trackBar_1stArm.Value = Arm_Init_Degree[3];
            trackBar_2ndArm.Value = Arm_Init_Degree[4];
            trackBar_3rdArm.Value = Arm_Init_Degree[5];
            trackBar_hand.Value = Arm_Init_Degree[6];

            Init_textBox_value();
            update_Degree(trackBar_rotateArm.Value, trackBar_1stArm.Value, trackBar_2ndArm.Value, trackBar_3rdArm.Value, trackBar_hand.Value, trackBar_cargo.Value);
        }

        private void Init_canvas()
        {
            for (int i = 0; i < totalParts; i++)
            {
                obj[i] = new objLoader(objFilePath, objName[i] + ".obj");
            }

            robot = new Robot(totalParts, objName);
            environment = new Environment(glControl_sideView.Width, glControl_sideView.Height);
        }

        private void glControl_sideView_Load(object sender, EventArgs e)
        {
            glControl_sideView.MakeCurrent();
            sideView = new Canvas();

            for (int i = 0; i < totalParts; i++)
            {
                sideView.shader[i] = new Shader("Shader/parts.vert", "Shader/parts.frag");
            }

            for (int i = 0; i < totalParts; i++)
            {
                sideView.shader[i].InitBuffers(obj[i].vertex, obj[i].faces);
            }

            sideView.camera = new Camera(new Vector3(0.05f, 0.1f, 0.6f), new Vector3(0, 0, -1.0f));

            GL.Viewport(0, 0, glControl_sideView.Width, glControl_sideView.Height);
            GL.Enable(EnableCap.DepthTest);
        }

        private void glControl_sideView_Paint(object sender, PaintEventArgs e)
        {
            model_sideView_Draw();
        }

        private void glControl_sideView_Resize(object sender, EventArgs e)
        {
            glControl_sideView.MakeCurrent();
            GL.Viewport(0, 0, glControl_sideView.Width, glControl_sideView.Height);
        }

        private void model_sideView_Draw()
        {
            glControl_sideView.MakeCurrent();
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            GL.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            for (int i = 0; i < totalParts; i++)
                sideView.shader[i].Draw(i, obj[i].faces, robot, sideView.camera, environment);

            glControl_sideView.SwapBuffers();
        }

        private void glControl_topView_Load(object sender, EventArgs e)
        {
            glControl_topView.MakeCurrent();
            topView = new Canvas();

            for (int i = 0; i < totalParts; i++)
            {
                topView.shader[i] = new Shader("Shader/parts.vert", "Shader/parts.frag");
            }

            for (int i = 0; i < totalParts; i++)
            {
                topView.shader[i].InitBuffers(obj[i].vertex, obj[i].faces);
            }

            topView.camera = new Camera(new Vector3(0.06f, 0.8f, 0.05f), new Vector3(-0.0001f, -1.0f, 0));

            GL.Viewport(0, 0, glControl_topView.Width, glControl_topView.Height);
            GL.Enable(EnableCap.DepthTest);
        }

        private void glControl_topView_Paint(object sender, PaintEventArgs e)
        {
            model_topView_Draw();
        }

        private void glControl_topView_Resize(object sender, EventArgs e)
        {
            glControl_topView.MakeCurrent();
            GL.Viewport(0, 0, glControl_topView.Width, glControl_topView.Height);
        }

        private void model_topView_Draw()
        {
            glControl_topView.MakeCurrent();
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            GL.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            for (int i = 0; i < totalParts; i++)
                topView.shader[i].Draw(i, obj[i].faces, robot, topView.camera, environment);

            glControl_topView.SwapBuffers();
        }

        private void update_dataNum()
        {
            FileStream fs = null;

            try
            {
                fs = new FileStream(csvFile, FileMode.Open, FileAccess.Read);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            if (fs != null)
            {
                StreamReader sw = new StreamReader(fs, Encoding.UTF8);

                data_num = -1;
                while (!sw.EndOfStream)
                {
                    sw.ReadLine();
                    data_num++;
                }

                textBox_data_num.Text = data_num.ToString();

                sw.Close();
                fs.Close();
            }
        }

        private void btn_Create_Click(object sender, EventArgs e)
        {
            string FileName = textBox_createFileName.Text;
            string FilePath = "./" + csvFileFolder + "/";

            if (FileName != string.Empty)
            {
                csvFile = FilePath + FileName + ".csv";
                textBox_FileName.Text = FileName + ".csv";
                textBox_FilePath.Text = FilePath;

                if (!File.Exists(csvFile))
                {
                    FileStream fs = null;
                    try
                    {
                        fs = new FileStream(csvFile, FileMode.Create, FileAccess.Write);
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.Message);
                    }

                    if (fs != null)
                    {
                        StreamWriter sw = new StreamWriter(fs, Encoding.UTF8);

                        string data = "Index,loading,rotate_arm,1st_arm,2nd_arm,3rd_arm,hand";
                        sw.WriteLine(data);

                        sw.Close();
                        fs.Close();
                    }
                }
                update_dataNum();
            }
        }

        private void btn_choseFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            openFile.Title = "Select File To Save Rotation Data";
            openFile.Filter = "csv file (.csv)|*.csv";
            openFile.FilterIndex = 1;
            openFile.InitialDirectory = Directory.GetCurrentDirectory() + "\\" + csvFileFolder;

            if (openFile.ShowDialog() == DialogResult.OK)
            {
                string csvFileFullName = openFile.FileName;
                string dirPath = Path.GetDirectoryName(csvFileFullName) + "\\";
                string csvFileName = csvFileFullName.Remove(0, csvFileFullName.LastIndexOf('\\') + 1);
                textBox_FilePath.Text = dirPath;
                textBox_FileName.Text = csvFileName;

                csvFile = dirPath + csvFileName;
                textBox_createFileName.Clear();
                update_dataNum();
            }
        }

        private void btn_save_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrEmpty(csvFile))
            {
                FileStream fs = null;

                try
                {
                    fs = new FileStream(csvFile, FileMode.Append, FileAccess.Write);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }

                if (fs != null)
                {

                    StreamWriter sw = new StreamWriter(fs, Encoding.UTF8);

                    string line = String.Format("{0},{1},{2},{3},{4},{5},{6}", data_num, trackBar_cargo.Value, trackBar_rotateArm.Value, trackBar_1stArm.Value, trackBar_2ndArm.Value, trackBar_3rdArm.Value, trackBar_hand.Value);
                    sw.WriteLine(line);

                    data_num++;
                    textBox_data_num.Text = data_num.ToString();

                    sw.Close();
                    fs.Close();
                }
            }
        }

        private void btn_delete_Click(object sender, EventArgs e)
        {
            if (data_num > 0 && !string.IsNullOrEmpty(csvFile))
            {
                FileStream fs = null;

                try
                {
                    fs = new FileStream(csvFile, FileMode.Open, FileAccess.Read);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }

                if (fs != null)
                {
                    StreamReader sr = new StreamReader(fs, Encoding.UTF8);
                    string content = sr.ReadToEnd();
                    sr.Close();
                    fs.Close();

                    fs = new FileStream(csvFile, FileMode.Create, FileAccess.Write);
                    StreamWriter sw = new StreamWriter(fs, Encoding.UTF8);

                    content = content.TrimEnd("\r\n".ToCharArray());
                    content = content.Remove(content.LastIndexOf('\r'));
                    sw.WriteLine(content);

                    data_num--;
                    textBox_data_num.Text = data_num.ToString();

                    sw.Close();
                    fs.Close();

                }
            }
        }

        private void textBox_createFileName_MouseDown(object sender, MouseEventArgs e)
        {
            isEntercsvFileName = true;
        }

        private void textBox_createFileName_Leave(object sender, EventArgs e)
        {
            isEntercsvFileName = false;
        }

        private void btn_delete_Click_1(object sender, EventArgs e)
        {
            if (!String.IsNullOrEmpty(csvFile))
            {
                bool isDeleted = false;
                try
                {
                    File.Delete(csvFile);
                    isDeleted = true;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                    isDeleted = false;
                }

                if (isDeleted)
                {
                    csvFile = string.Empty;
                    textBox_FileName.Text = string.Empty;
                    textBox_FilePath.Text = string.Empty;
                    textBox_data_num.Text = string.Empty;
                }
            }
        }

        private void btn_chooseActionListFolder_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog folder = new FolderBrowserDialog();
            string curPath = Directory.GetCurrentDirectory();
            folder.Description = "choose Action Folder";
            folder.SelectedPath = curPath;

            if (folder.ShowDialog() == DialogResult.OK)
            {
                textBox_ActionListFolder.Text = folder.SelectedPath;

                updateActionList();
            }
        }

        private void updateActionList()
        {
            listView_ActionList.Items.Clear();

            if (!String.IsNullOrEmpty(textBox_ActionListFolder.Text))
            {
                string[] csvActionFiles = Directory.GetFiles(textBox_ActionListFolder.Text, "*.csv");

                if (csvActionFiles != null)
                {
                    int idx;
                    string FileName;
                    foreach (string csvActionFile in csvActionFiles)
                    {
                        idx = csvActionFile.LastIndexOf('\\');
                        FileName = csvActionFile.Remove(0, idx + 1);
                        listView_ActionList.Items.Add(FileName);
                    }
                }
            }
        }

        private void btn_ActionList_refresh_Click(object sender, EventArgs e)
        {
            updateActionList();
        }

        private void btn_ActionList_play_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrEmpty(textBox_ActionListFolder.Text) && listView_ActionList.SelectedIndices.Count > 0)
            {
                int idx = listView_ActionList.SelectedIndices[0];
                string file = textBox_ActionListFolder.Text + '\\' + listView_ActionList.Items[idx].Text;

                FileStream fs = null;
                try
                {
                    fs = new FileStream(file, FileMode.Open, FileAccess.Read);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }

                if (fs != null)
                {
                    StreamReader sw = new StreamReader(fs, Encoding.UTF8);

                    int line_num = 0;
                    string line;
                    string[] split_line;
                    int[] val;

                    while (!sw.EndOfStream)
                    {
                        line = sw.ReadLine();
                        split_line = line.Split(',');
                        val = new int[split_line.Length];

                        line_num++;

                        if (line_num == 1)
                            continue;


                        for (int i = 0; i < split_line.Length; i++)
                        {
                            //Index 欄位
                            if (i == 0)
                                continue;

                            val[i] = int.Parse(split_line[i]);
                            string str = String.Format("#{0}_{1}#", i + 1, deg2Data(int.Parse(split_line[i])));
                            SendData(str);
                        }

                        update_Degree(val[2], val[3], val[4], val[5], val[6], val[1]);
                    }

                    sw.Close();
                    fs.Close();
                }
            }
        }
    }
}
