using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Management;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Bluetooth
{
    public partial class Form1 : Form
    {
        const int maxTransmitBytes = 10;
        string[] myKeys;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            RefreshComport();
            myKeys = new string[] { "W", "A", "S", "D", "Q", "E", "C", "Z", "R", "Space", "ControlKey", "Up", "Down", "Left", "Right", "ShiftKey", "Return" };
        }

        private void DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort spl = (SerialPort)sender;
            string data = spl.ReadExisting();
            serialPort1.DiscardInBuffer();

            Task task = new Task(() =>
            {
                if (textBox_log.InvokeRequired && data.Length > 0)
                {
                    //去除掉'\0'字元
                    string temp = data.Remove(data.Length - 1);
                    Action updatetextBox_Log = new Action(() => addLog(temp));
                    textBox_log.Invoke(updatetextBox_Log);
                }
            });

            task.Start();
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
                SendData(myKeys[index]);


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

            e.Handled = true;
            textBox_log.Focus();
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

                        addLog("Open " + serialPort1.PortName);
                        addLog("Connected...");

                        serialPort1.DataReceived += new SerialDataReceivedEventHandler(DataReceived);

                        timer1.Interval = 10000;
                        timer1.Start();
                    }
                }
                catch (Exception ex)
                {
                    addLog(ex.Message);
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
                    addLog("Close " + serialPort1.PortName);
                }
            }
            catch (Exception ex)
            {
                addLog(ex.Message);
            }
        }

        private void addLog(string str)
        {
            textBox_log.Text += String.Format("{0} - {1} {2}", DateTime.Now.ToString("hh:mm:ss"), str, Environment.NewLine);
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

        private void button_refresh_Click(object sender, EventArgs e)
        {
            RefreshComport();
        }

        private void textBox_log_TextChanged(object sender, EventArgs e)
        {
            textBox_log.SelectionStart = textBox_log.Text.Length;
            textBox_log.ScrollToCaret();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            SendData("con");
        }

        private void textBox_log_Leave(object sender, EventArgs e)
        {
            textBox_log.Focus();
        }
    }
}
