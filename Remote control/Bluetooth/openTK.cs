using System;
using System.Collections.Generic;
using System.IO;
using OpenTK;
using OpenTK.Graphics.OpenGL;

namespace Bluetooth
{

    public class Vertex
    {
        public List<float> vertice = new List<float>();
        //public List<float> texture = new List<float>();
        public List<float> normal = new List<float>();
    }

    public class Indice
    {
        public List<uint> vertice = new List<uint>();
        //public List<uint> texture = new List<uint>();
        public List<uint> normal = new List<uint>();
    }

    public class Material
    {
        public Vector3 Ka;
        public Vector3 Kd;
        public Vector3 Ks;
    }

    public class Face
    {
        public Indice indices = new Indice();
        public Material material = new Material();
    }

    class objLoader
    {

        public Vertex vertex = new Vertex();
        public Face[] faces;

        public objLoader(string folderPath, string fileName)
        {
            loadFile(folderPath, fileName);
        }


        private void loadFile(String folderPath, String fileName)
        {
            StreamReader objReader = new StreamReader(folderPath + fileName);
            string obj_line = "";
            int usemtl_num = 1;

            while (objReader.Peek() != -1)
            {
                obj_line = objReader.ReadLine();

                if (obj_line.Length < 2) continue;

                string[] obj_str = obj_line.Split(' ');

                if (obj_str[0] == "mtllib")
                {
                    StreamReader mtlReader = new StreamReader(folderPath + obj_str[1]);

                    string mtl_line = "";
                    int mat_counter = -1;

                    while (mtlReader.Peek() != -1)
                    {
                        mtl_line = mtlReader.ReadLine();
                        string[] mtl_str = mtl_line.Split(' ');

                        if (mtl_str[0] == "#" && mtl_str[1] == "num_materials:")
                        {
                            int num_material = Int16.Parse(mtl_str[2]);
                            faces = new Face[num_material];
                            for (int i = 0; i < num_material; i++)
                            {
                                faces[i] = new Face();
                            }
                        }

                        if (mtl_str[0] == "newmtl")
                            mat_counter++;


                        if (mtl_str[0] == "Ka")
                        {
                            float[] val = new float[3];

                            for (int i = 0; i < 3; i++)
                                val[i] = float.Parse(mtl_str[3 * i + 2]);

                            faces[mat_counter].material.Ka = new Vector3(val[0], val[1], val[2]);
                        }

                        if (mtl_str[0] == "Kd")
                        {
                            float[] val = new float[3];

                            for (int i = 0; i < 3; i++)
                                val[i] = float.Parse(mtl_str[3 * i + 2]);

                            faces[mat_counter].material.Kd = new Vector3(val[0], val[1], val[2]);
                        }

                        if (mtl_str[0] == "Ks")
                        {
                            float[] val = new float[3];

                            for (int i = 0; i < 3; i++)
                                val[i] = float.Parse(mtl_str[3 * i + 2]);

                            faces[mat_counter].material.Ks = new Vector3(val[0], val[1], val[2]);
                        }
                    }

                    mtlReader.Close();
                }

                if (obj_str[0] == "usemtl")
                    usemtl_num = int.Parse(obj_str[2]) - 1;

                if (obj_str[0] == "v")
                {
                    float[] vertice = new float[3];
                    vertice[0] = float.Parse(obj_str[1]);
                    vertice[1] = float.Parse(obj_str[2]);
                    vertice[2] = float.Parse(obj_str[3]);
                    vertex.vertice.AddRange(vertice);
                }

                if (obj_str[0] == "vn")
                {
                    float[] normal = new float[3];
                    normal[0] = float.Parse(obj_str[1]);
                    normal[1] = float.Parse(obj_str[2]);
                    normal[2] = float.Parse(obj_str[3]);
                    vertex.normal.AddRange(normal);
                }

                //if (obj_str[0] == "vt")
                //{
                //    float[] texture = new float[2];
                //    texture[0] = float.Parse(obj_str[1]);
                //    texture[1] = float.Parse(obj_str[2]);
                //    vertex.texture.AddRange(texture);
                //}

                if (obj_str[0] == "f")
                {
                    uint[] vertice = new uint[3];
                    //uint[] texture = new uint[3];
                    uint[] normal = new uint[3];

                    for (int i = 0; i < 3; i++)
                    {
                        string[] index = obj_str[i + 1].Split('/');
                        vertice[i] = uint.Parse(index[0]) - 1;
                        //texture[i] = uint.Parse(index[1]) - 1;
                        normal[i] = uint.Parse(index[2]) - 1;
                    }

                    faces[usemtl_num].indices.vertice.AddRange(vertice);
                    faces[usemtl_num].indices.normal.AddRange(normal);
                }
            }

            objReader.Close();
        }
    }

    class Shader
    {
        int program;
        int vertex;
        int fragment;
        string vertexFileName;
        string fragmentFileName;

        int VAO;
        int VBO;
        int EBO;

        public Shader(string _vertexFileName, string _fragmentFileName)
        {
            vertexFileName = _vertexFileName;
            fragmentFileName = _fragmentFileName;

            CreateShaders();
            CreateProgram();
        }

        private void CreateShaders()
        {
            vertex = GL.CreateShader(ShaderType.VertexShader);
            string vertexSource = File.ReadAllText(vertexFileName);

            GL.ShaderSource(vertex, vertexSource);
            GL.CompileShader(vertex);

            string infoLogVertex = GL.GetShaderInfoLog(vertex);
            if (infoLogVertex != string.Empty)
                Console.WriteLine(infoLogVertex);

            fragment = GL.CreateShader(ShaderType.FragmentShader);
            string fragmentSource = File.ReadAllText(fragmentFileName);

            GL.ShaderSource(fragment, fragmentSource);
            GL.CompileShader(fragment);

            string infoLogFragment = GL.GetShaderInfoLog(fragment);
            if (infoLogFragment != string.Empty)
                Console.WriteLine(infoLogFragment);
        }

        private void CreateProgram()
        {
            program = GL.CreateProgram();
            GL.AttachShader(program, vertex);
            GL.AttachShader(program, fragment);
            GL.LinkProgram(program);

            GL.DeleteShader(vertex);
            GL.DeleteShader(fragment);
        }

        public void InitBuffers(Vertex vertex, Face[] faces)
        {
            VAO = GL.GenVertexArray();
            VBO = GL.GenBuffer();
            EBO = GL.GenBuffer();

            float[] vertices = vertex.vertice.ToArray();
            float[] normals = vertex.normal.ToArray();


            int faces_num = faces.Length;

            List<uint> idx_vertices_list = new List<uint>();
            List<uint> idx_normals_list = new List<uint>();

            for (int i = 0; i < faces_num; i++)
            {
                idx_vertices_list.AddRange(faces[i].indices.vertice);
                idx_normals_list.AddRange(faces[i].indices.normal);
            }

            uint[] idx_vertices = idx_vertices_list.ToArray();
            uint[] idx_normals = idx_normals_list.ToArray();

            GL.BindVertexArray(VAO);

            GL.BindBuffer(BufferTarget.ArrayBuffer, VBO);
            GL.BufferData(BufferTarget.ArrayBuffer, (vertices.Length + normals.Length) * sizeof(float), IntPtr.Zero, BufferUsageHint.StaticDraw);
            GL.BufferSubData(BufferTarget.ArrayBuffer, (IntPtr)0, vertices.Length * sizeof(float), vertices);
            GL.BufferSubData(BufferTarget.ArrayBuffer, (IntPtr)(vertices.Length * sizeof(float)), normals.Length * sizeof(float), normals);

            GL.BindBuffer(BufferTarget.ElementArrayBuffer, EBO);
            GL.BufferData(BufferTarget.ElementArrayBuffer, (idx_vertices.Length + idx_normals.Length) * sizeof(uint), IntPtr.Zero, BufferUsageHint.StaticDraw);
            GL.BufferSubData(BufferTarget.ElementArrayBuffer, (IntPtr)0, idx_vertices.Length * sizeof(uint), idx_vertices);
            GL.BufferSubData(BufferTarget.ElementArrayBuffer, (IntPtr)(idx_vertices.Length * sizeof(uint)), idx_normals.Length * sizeof(uint), idx_normals);


            GL.EnableVertexAttribArray(0);
            GL.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, 0, (IntPtr)0);

            GL.EnableVertexAttribArray(1);
            GL.VertexAttribPointer(1, 3, VertexAttribPointerType.Float, false, 0, (IntPtr)(vertices.Length * sizeof(float)));

            GL.BindVertexArray(0);
        }

        public void Draw(int model_num, Face[] faces, Robot robot, Camera camera, Environment environment)
        {
            for (int i = 0; i < faces.Length; i++)
            {
                Draw_face(model_num, i, faces, robot, camera, environment);
            }
        }

        private void Draw_face(int model_num, int Face_num, Face[] faces, Robot robot, Camera camera, Environment environment)
        {
            GL.UseProgram(program);

            GL.BindVertexArray(VAO);

            //vertex shader
            GL.Uniform3(GL.GetUniformLocation(program, "texture.a_Ka"), faces[Face_num].material.Ka);
            GL.Uniform3(GL.GetUniformLocation(program, "texture.a_Kd"), faces[Face_num].material.Kd);
            GL.Uniform3(GL.GetUniformLocation(program, "texture.a_Ks"), faces[Face_num].material.Ks);

            GL.UniformMatrix4(GL.GetUniformLocation(program, "modelMat"), 1, false, Matrix4ToArray(robot.modelMat[model_num]));
            GL.UniformMatrix4(GL.GetUniformLocation(program, "viewMat"), 1, false, Matrix4ToArray(camera.viewMat));
            GL.UniformMatrix4(GL.GetUniformLocation(program, "projMat"), 1, false, Matrix4ToArray(environment.projMat));

            //fragment shader
            //GL.Uniform3(GL.GetUniformLocation(program, "lightPos"), 0.0f, 0.0f, 5.0f);
            GL.Uniform3(GL.GetUniformLocation(program, "lightPos"), camera.Position.X, camera.Position.Y, camera.Position.Z);
            GL.Uniform3(GL.GetUniformLocation(program, "cameraPos"), camera.Position.X, camera.Position.Y, camera.Position.Z);

            GL.Uniform3(GL.GetUniformLocation(program, "objectColor"), 1.0f, 1.0f, 1.0f);
            GL.Uniform3(GL.GetUniformLocation(program, "ambientColor"), 0.1f, 0.1f, 0.1f);
            GL.Uniform3(GL.GetUniformLocation(program, "lightColor"), 1.0f, 1.0f, 1.0f);

            GL.Uniform3(GL.GetUniformLocation(program, "light.ambient"), environment.ambient);
            GL.Uniform3(GL.GetUniformLocation(program, "light.diffuse"), environment.diffuse);
            GL.Uniform3(GL.GetUniformLocation(program, "light.specular"), environment.specular);
            GL.Uniform1(GL.GetUniformLocation(program, "light.shininess"), environment.shininess);

            int start = 0;

            for (int i = 0; i < Face_num; i++)
                start += faces[i].indices.vertice.Count;

            GL.DrawElements(PrimitiveType.Triangles, faces[Face_num].indices.vertice.Count, DrawElementsType.UnsignedInt, start * sizeof(float));

            GL.BindVertexArray(0);
        }

        private float[] Matrix4ToArray(Matrix4 mat)
        {
            float[] data = new float[16];
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    data[i * 4 + j] = mat[i, j];

            return data;
        }
    }

    class Robot
    {

        public float[] rotateDegree;

        public Matrix4[] modelMat;
        public Matrix4[] transMat;
        public Matrix4[] rotateMat;

        Vector3[] Position;
        Vector3[] rotateAxis;

        int DOF;
        string[] partsName;

        public Robot(int _totalparts, string[] _partsName)
        {
            DOF = _totalparts - 1;
            partsName = _partsName;
            rotateDegree = new float[DOF];

            Init_Position();
            Init_roateAxis();
            Init_Matrix();
            updateMatrix();
        }

        public int Idx(string partName)
        {
            return Array.IndexOf(partsName, partName);
        }

        private void Init_Position()
        {
            Position = new Vector3[DOF];

            Position[Idx("hand_left")] = new Vector3(-83.40f, -3.00f, 12.10f);
            Position[Idx("hand_right")] = new Vector3(-83.40f, -3.00f, -11.90f);
            Position[Idx("third_arm")] = new Vector3(-30.50f, 70.00f, 27.50f);
            Position[Idx("rotate_arm")] = new Vector3(0.00f, 0.00f, 0.00f);
            Position[Idx("first_arm")] = new Vector3(0.00f, 67.50f, 27.50f);
            Position[Idx("second_arm")] = new Vector3(0.00f, 171.90f, 27.50f);

            Position[Idx("cargo")] = new Vector3(165.00f, 3.90f, -15.60f);

            for (int i = 0; i < DOF; i++)
                Position[i] *= 0.001f;
        }

        private void Init_roateAxis()
        {
            rotateAxis = new Vector3[DOF];

            rotateAxis[Idx("hand_left")] = new Vector3(0, 1.0f, 0);
            rotateAxis[Idx("hand_right")] = new Vector3(0, 1.0f, 0);
            rotateAxis[Idx("third_arm")] = new Vector3(0, 0, 1.0f);
            rotateAxis[Idx("rotate_arm")] = new Vector3(0, 1.0f, 0);
            rotateAxis[Idx("first_arm")] = new Vector3(0, 0, 1.0f);
            rotateAxis[Idx("second_arm")] = new Vector3(0, 0, 1.0f);

            rotateAxis[Idx("cargo")] = new Vector3(0, 0, 1.0f);
        }

        private void Init_Matrix()
        {
            modelMat = new Matrix4[DOF + 1];
            transMat = new Matrix4[DOF];
            rotateMat = new Matrix4[DOF];

            for (int i = 0; i < DOF; i++)
                transMat[i] = Matrix4.CreateTranslation(Position[i]);
        }

        public void updateMatrix()
        {
            for (int i = 0; i < DOF; i++)
                rotateMat[i] = Matrix4.CreateFromAxisAngle(rotateAxis[i], MathHelper.DegreesToRadians(rotateDegree[i]));

            modelMat[Idx("body")] = Matrix4.Identity;

            modelMat[Idx("rotate_arm")] = transMat[Idx("rotate_arm")] * rotateMat[Idx("rotate_arm")];

            modelMat[Idx("first_arm")] = rotateMat[Idx("first_arm")] *
                                          Matrix4.CreateTranslation(Position[Idx("first_arm")] - Position[Idx("rotate_arm")]) *
                                          rotateMat[Idx("rotate_arm")];

            modelMat[Idx("second_arm")] = rotateMat[Idx("second_arm")] *
                                         Matrix4.CreateTranslation(Position[Idx("second_arm")] - Position[Idx("first_arm")]) *
                                         modelMat[Idx("first_arm")];

            modelMat[Idx("third_arm")] = rotateMat[Idx("third_arm")] *
                                        Matrix4.CreateTranslation(Position[Idx("third_arm")] - Position[Idx("second_arm")]) *
                                        modelMat[Idx("second_arm")];

            modelMat[Idx("hand_left")] = rotateMat[Idx("hand_left")] *
                                         Matrix4.CreateTranslation(Position[Idx("hand_left")] - Position[Idx("third_arm")]) *
                                         modelMat[Idx("third_arm")];

            modelMat[Idx("hand_right")] = rotateMat[Idx("hand_right")]*
                                          Matrix4.CreateTranslation(Position[Idx("hand_right")] - Position[Idx("third_arm")]) *
                                          modelMat[Idx("third_arm")];

            modelMat[Idx("cargo")] = rotateMat[Idx("cargo")] * transMat[Idx("cargo")];
        }
    }


    class Camera
    {
        public Matrix4 viewMat;

        public Vector3 Position;
        public Vector3 Front;

        public Vector3 Right;
        public Vector3 Up;
        Vector3 worldUp;

        public Camera(Vector3 _Position, Vector3 _Front)
        {
            Position = _Position;
            Front = _Front;

            worldUp = new Vector3(0, 1.0f, 0);

            update_viewMat();
        }

        private void update_viewMat()
        {
            viewMat = Matrix4.LookAt(Position, Position + Front, worldUp);
        }
    }

    class Environment
    {
        public Matrix4 projMat;
        float aspect;

        public Vector3 diffuse;
        public Vector3 specular;
        public Vector3 ambient;
        public float shininess;


        public Environment(int width, int height)
        {
            aspect = (float)width / height;

            Init_projMat();
            Init_light();
        }

        private void Init_projMat()
        {
            projMat = Matrix4.CreatePerspectiveFieldOfView(MathHelper.DegreesToRadians(45.0f), aspect, 0.1f, 100.0f);
        }


        private void Init_light()
        {
            diffuse = new Vector3(0.1f);
            specular = new Vector3(0.1f);
            ambient = new Vector3(0.5f);
            shininess = 32.0f;
        }
    }
}


