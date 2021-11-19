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
        const byte SERVO_HEADER = 0xF0;
        const byte SERVO_ENDING = 0xF0;
        const byte SERVO_EN_HEADER = 0xF1;
        const byte SERVO_EN_ENDING = 0xF1;
        const byte MOVEMENT_HEADER = 0xF2;
        const byte MOVEMENT_ENDING = 0xF2;
        const byte SENSOR_HEADER = 0xF3;
        const byte SENSOR_ENDING = 0xF4;

        const int Mode_HRDE = 0;
        const int Mode_HDE = 1;

        char[] myKeys = new char[] { 'W', 'A', 'S', 'D', 'Q', 'E', 'C', 'Z', 'R', 'V' };
        int[] Arm_Init_Degree = new int[7] { 0, 0, 0, 90, -90, 0, 4 };

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

        bool isReceivingSensorData = false;
        int sensorData;
        int sensorData_counter;

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
            //Master 端要把所有的printf關掉 否則PC端會收到

            SerialPort spl = (SerialPort)sender;
            int data_Byte = spl.ReadByte();

            if (isReceivingSensorData == true && sensorData_counter < 2)
            {
                sensorData += data_Byte << 8 * (1 - sensorData_counter);
                sensorData_counter++;
            }


            if (data_Byte == SENSOR_HEADER && isReceivingSensorData == false)
            {
                isReceivingSensorData = true;
                sensorData = 0;
                sensorData_counter = 0;
            }

            if (data_Byte == SENSOR_ENDING && isReceivingSensorData == true && sensorData_counter == 2)
            {
                isReceivingSensorData = false;
                updateSensorColor();
            }
        }

        private bool checkBit(int pos)
        {
            return (sensorData & (1 << pos)) != 0;
        }

        private void updateSensorColor()
        {
            if (checkBit(14))
                Sensor_right_behind_ground.BackColor = Color.Red;
            else
                Sensor_right_behind_ground.BackColor = Color.Green;

            if (checkBit(13))
                Sensor_right_behind_right.BackColor = Color.Red;
            else
                Sensor_right_behind_right.BackColor = Color.Green;

            if (checkBit(12))
                Sensor_right_behind_behind.BackColor = Color.Red;
            else
                Sensor_right_behind_behind.BackColor = Color.Green;

            if (checkBit(11))
                Sensor_left_behind_ground.BackColor = Color.Red;
            else
                Sensor_left_behind_ground.BackColor = Color.Green;

            if (checkBit(10))
                Sensor_left_behind_left.BackColor = Color.Red;
            else
                Sensor_left_behind_left.BackColor = Color.Green;

            if (checkBit(9))
                Sensor_left_behind_behind.BackColor = Color.Red;
            else
                Sensor_left_behind_behind.BackColor = Color.Green;

            if (checkBit(8))
                Sensor_right_front_ground.BackColor = Color.Red;
            else
                Sensor_right_front_ground.BackColor = Color.Green;

            if (checkBit(7))
                Sensor_right_front_right.BackColor = Color.Red;
            else
                Sensor_right_front_right.BackColor = Color.Green;

            if (checkBit(6))
                Sensor_right_front_front.BackColor = Color.Red;
            else
                Sensor_right_front_front.BackColor = Color.Green;

            if (checkBit(4))
                Sensor_hand_front.BackColor = Color.Red;
            else
                Sensor_hand_front.BackColor = Color.Green;

            if (checkBit(2))
                Sensor_left_front_ground.BackColor = Color.Red;
            else
                Sensor_left_front_ground.BackColor = Color.Green;

            if (checkBit(1))
                Sensor_left_front_left.BackColor = Color.Red;
            else
                Sensor_left_front_left.BackColor = Color.Green;

            if (checkBit(0))
                Sensor_left_front_front.BackColor = Color.Red;
            else
                Sensor_left_front_front.BackColor = Color.Green;
        }

        public void SendData(int Mode, byte Header, byte RegAdd, byte Data, byte Ending)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.DiscardOutBuffer();
                byte[] sendData;
                try
                {
                    switch (Mode)
                    {
                        // Data 高位元組 跟低位元組
                        case Mode_HRDE:
                            sendData = new byte[4];
                            sendData[0] = Header;
                            sendData[1] = RegAdd;
                            sendData[2] = Data;
                            sendData[3] = Ending;
                            serialPort1.Write(sendData, 0, 4);
                            break;

                        case Mode_HDE:
                            sendData = new byte[3];
                            sendData[0] = Header;
                            sendData[1] = Data;
                            sendData[2] = Ending;
                            serialPort1.Write(sendData, 0, 3);
                            break;
                    }
                }
                catch (Exception ex)
                {
                    btn_open.Enabled = true;
                    btn_close.Enabled = false;

                    close_comPort();

                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (serialPort1.IsOpen && !isEntercsvFileName)
            {
                int index = Array.IndexOf(myKeys, e.KeyCode.ToString().ToCharArray()[0]);

                if (index > -1)
                    SendData(Mode_HDE, MOVEMENT_HEADER, 0, Convert.ToByte(myKeys[index]), MOVEMENT_ENDING);
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

                case Keys.V:
                    btn_V.BackColor = Color.Yellow;
                    btn_V.ForeColor = Color.Black;
                    break;
            }

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

            btn_V.BackColor = Color.Black;
            btn_V.ForeColor = Color.White;
        }

        private void btn_open_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrEmpty(comboBox_port.Text))
            {
                serialPort1.PortName = comboBox_port.Text;
                serialPort1.BaudRate = 38400;
                serialPort1.DataBits = 8;
                serialPort1.StopBits = StopBits.One;
                serialPort1.DtrEnable = true;
                serialPort1.RtsEnable = true;
                serialPort1.WriteTimeout = 500;
                serialPort1.ReadTimeout = 500;

                try
                {
                    if (!serialPort1.IsOpen)
                    {
                        serialPort1.DataReceived += new SerialDataReceivedEventHandler(DataReceived);

                        serialPort1.Open();

                        btn_open.Enabled = false;
                        btn_close.Enabled = true;
                        comboBox_port.Enabled = false;
                        isReceivingSensorData = false;
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
                comboBox_port.Enabled = true;

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
            isReceivingSensorData = false;

            serialPort1.DataReceived -= DataReceived;
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
            if (!serialPort1.IsOpen)
                RefreshComport();
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
            robot.rotateDegree[robot.Idx("rotate_arm")] = 90 - rotate_arm;
            robot.rotateDegree[robot.Idx("first_arm")] = 90 - first_arm;
            robot.rotateDegree[robot.Idx("second_arm")] = -90 - second_arm;
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
            robot.rotateDegree[robot.Idx("rotate_arm")] = 90 - trackBar_rotateArm.Value;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_rotateArm_MouseUp(object sender, MouseEventArgs e)
        {
            SendData(Mode_HRDE, SERVO_HEADER, 2, deg2Byte(trackBar_rotateArm.Value), SERVO_ENDING);
        }

        private void trackBar_1stArm_Scroll(object sender, EventArgs e)
        {
            textBox_1stArm.Text = trackBar_1stArm.Value.ToString();
            robot.rotateDegree[robot.Idx("first_arm")] = 90 - trackBar_1stArm.Value;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_1stArm_MouseUp(object sender, MouseEventArgs e)
        {
            SendData(Mode_HRDE, SERVO_HEADER, 3, deg2Byte(trackBar_1stArm.Value), SERVO_ENDING);
        }

        private void trackBar_2ndArm_Scroll(object sender, EventArgs e)
        {
            textBox_2ndArm.Text = trackBar_2ndArm.Value.ToString();
            robot.rotateDegree[robot.Idx("second_arm")] = -90 - trackBar_2ndArm.Value;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_2ndArm_MouseUp(object sender, MouseEventArgs e)
        {
            SendData(Mode_HRDE, SERVO_HEADER, 4, deg2Byte(trackBar_2ndArm.Value), SERVO_ENDING);
        }

        private void trackBar_3rdArm_Scroll(object sender, EventArgs e)
        {
            textBox_3rdArm.Text = trackBar_3rdArm.Value.ToString();

            robot.rotateDegree[robot.Idx("third_arm")] = -trackBar_3rdArm.Value;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_3rdArm_MouseUp(object sender, MouseEventArgs e)
        {
            SendData(Mode_HRDE, SERVO_HEADER, 5, deg2Byte(trackBar_3rdArm.Value), SERVO_ENDING);
        }

        private void trackBar_hand_Scroll(object sender, EventArgs e)
        {
            textBox_hand.Text = trackBar_hand.Value.ToString();
            robot.rotateDegree[robot.Idx("hand_left")] = trackBar_hand.Value;
            robot.rotateDegree[robot.Idx("hand_right")] = -robot.rotateDegree[robot.Idx("hand_left")];

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_hand_MouseUp(object sender, MouseEventArgs e)
        {
            SendData(Mode_HRDE, SERVO_HEADER, 6, deg2Byte(trackBar_hand.Value), SERVO_ENDING);
        }

        private void trackBar_cargo_Scroll(object sender, EventArgs e)
        {
            textBox_cargo.Text = trackBar_cargo.Value.ToString();
            robot.rotateDegree[robot.Idx("cargo")] = trackBar_cargo.Value;

            robot.updateMatrix();
            model_sideView_Draw();
            model_topView_Draw();
        }

        private void trackBar_cargo_MouseUp(object sender, MouseEventArgs e)
        {
            SendData(Mode_HRDE, SERVO_HEADER, 0, deg2Byte(trackBar_cargo.Value), SERVO_ENDING);
        }

        private byte deg2Byte(int num)
        {
            return Convert.ToByte(num + 128);
        }

        private void btn_ResetArm_Click(object sender, EventArgs e)
        {
            for (byte i = 0; i < Arm_Init_Degree.Length; i++)
            {
                //車斗 i=0 和 i=1 數值相同在Master會做處理
                if (i == 1)
                    continue;

                SendData(Mode_HRDE, SERVO_HEADER, i, deg2Byte(Arm_Init_Degree[i]), SERVO_ENDING);
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
                            val[i] = int.Parse(split_line[i]);
                        }

                        for (int i = split_line.Length - 1; i > 0; i--)
                        {
                            SendData(Mode_HRDE, SERVO_HEADER, Convert.ToByte(i), deg2Byte(int.Parse(split_line[i])), SERVO_ENDING);
                        }

                        update_Degree(val[2], val[3], val[4], val[5], val[6], val[1]);
                        Thread.Sleep(500);
                    }

                    sw.Close();
                    fs.Close();
                }
            }
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
    }
}
