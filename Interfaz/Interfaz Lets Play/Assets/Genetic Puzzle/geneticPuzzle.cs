using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Client;
using UnityEditor.SearchService;
using UnityEngine.SceneManagement;
using System;

using UnityEditor;
using System.IO;

public class geneticPuzzle : MonoBehaviour
{
    public RawImage image0;
    public RawImage image1;
    public RawImage image2;
    public RawImage image3;
    public RawImage image4;
    public RawImage image5;
    public RawImage image6;
    public RawImage image7;
    public RawImage image8;
    public RawImage image9;
    public RawImage image10;
    public RawImage image11;
    public RawImage image12;
    public RawImage image13;
    public RawImage image14;
    public RawImage image15;
    public RawImage image16;
    public RawImage image17;
    public RawImage image18;
    public RawImage image19;
    public RawImage image20;
    public RawImage image21;
    public RawImage image22;
    public RawImage image23;
    public RawImage image24;

    public Button ButtonNext;
    public Button ButtonPrev;

    public Slider mySlider;

    // mensaje que recibe del server 
    string startMessage;

    // cantidad de divisiones
    int howMuchImg;

    //matriz de cada generacion
    static int[,] matrix;


    // string con todas las generaciones 
    string geneticString;

    // matriz con cada generacion por separado 
    static string[] geneticBest;

    static string[] genList;

    // rows
    static int globalRows;

    // columns
    static int globalCol;

    static int currentGen = 0;

    static int currentDispaly = 0;

    List<int[,]> resultMatrices = new List<int[,]>();

    string[] divString(string str, string identifier)
    {
        string[] divided = str.Split(identifier.ToCharArray());
        return divided;
    }

    int[,] DeepCopy(int[,] original)
    {
        int[,] copy = new int[globalRows,globalCol];

        for (int i = 0; i < original.GetLength(0); i++)
        {
            for (int j = 0; j < original.GetLength(1); j++)
            {
                copy[i,j] = original[i,j];
            }
        }
        return copy;
    }

    void TaskOnClickNext()
    {
        if(currentDispaly + 1 != genList.Length -1){
            currentDispaly = currentDispaly +1;
            updateImages(howMuchImg, resultMatrices[currentDispaly]);
            
        } else {
            Debug.Log("no hay siguiente generacion");
        }
        
    }

    public void Imprimir(int[,] mat)
    {
        string tmp = "";
        for (int f = 0; f < globalRows; f++)
        {
            for (int c = 0; c < globalCol; c++)
            {
                tmp += "-" + mat[f, c] + " - ";
            }
            tmp += "/";
        }
        Debug.Log(tmp);

    }
    void TaskOnClickPrev()
    {
        if(currentDispaly > -1){
            currentDispaly = currentDispaly -1;
            if (currentDispaly != -1){
                updateImages(howMuchImg, resultMatrices[currentDispaly]);
            }
        } else {
            Debug.Log("no hay anterior generacion");
        }
    }


    int[,] apply_chain(string[] chain, int[,] prevMatrix) 
    {
        for (int i = 0; i < chain.Length; ++i) 
        {
            string apply = chain[i];
            if (apply == "up"){move_up(ref prevMatrix);}
            else if (apply == "down"){ move_down(ref prevMatrix);}
            else if (apply == "left"){ move_left(ref prevMatrix);}
            else if (apply == "right"){move_right(ref prevMatrix);}
        }
        return prevMatrix;

    }

    int[] find_0(int num, int[,] matrix_) 
    {
        int x = -1;
        int y = -1;
        int[] myvector = {0,0};

        for (int i = 0; i < matrix_.GetLength(0); i++)
        {
            x++;
            for (int j = 0; j < matrix_.GetLength(1); j++)
            {
                y++;
                if(matrix_[i,j] == num){
                    myvector[0] = x;
                    myvector[1] = y;
                    return myvector;
                }
            }
            y = -1;
        }
        myvector[0] = -1;
        myvector[1] = -1;
        return myvector;

    }

    void swap(int[] a, int[] b, ref int [,] matrix_)
    {
        int a1 = a[0];
        int a2 = a[1];
        int b1 = b[0];
        int b2 = b[1];
        int aux = matrix_[a1, a2];
        matrix_[a1, a2] = matrix_[b1, b2];
        matrix_[b1,b2] = aux;
    }

    void move_down(ref int[,] matrix_)
    {
        int[] index = find_0(0, matrix_);
        if (index[0] == 0){
            return ;
        }
        int[] move_to = {index[0] - 1, index[1]};
        swap(index, move_to, ref matrix_);
        return ;
    }

    void move_up(ref int[,] matrix_)
    {
        int[] index = find_0(0, matrix_);
        if (index[0] >= (globalRows - 1)){
            return ;
        }
        int[] move_to = {index[0] + 1, index[1] };
        swap(index, move_to, ref matrix_);
        return ;
    }
    void move_left(ref int[,] matrix_)
    {
        int[] index = find_0(0, matrix_);
        if (index[1] >= (globalCol - 1)){
            return ;
        }
        int[] move_to = {index[0], index[1] + 1};
        swap(index, move_to, ref matrix_);
        return ;
    }
    void move_right(ref int[,] matrix_)
    {
        int[] index = find_0(0, matrix_);
        if (index[1] == 0){
            return ;
        }
        int[] move_to = {index[0], index[1] - 1};
        swap(index, move_to, ref matrix_);
        return ;
    }

    // Start is called before the first frame update
    void Start()
    {
        Slider slider = mySlider.GetComponent<Slider>();
   

        // asigna la funcion a los botones 
        Button btnNext = ButtonNext.GetComponent<Button>();
        btnNext.onClick.AddListener(TaskOnClickNext);

        Button btnPrev = ButtonPrev.GetComponent<Button>();
        btnPrev.onClick.AddListener(TaskOnClickPrev);

        // Lee el string del servidor
        startMessage = SocketClient.MessageR;
        Debug.Log(startMessage);

        Debug.Log(divString(startMessage, "&")[0]);

        // divide el string en [0] matriz [1] geneticBest [2] numero de divisiones  
        string[] posString = divString(startMessage, "&");

        // inicializa la matriz segun el numero de divisiones 

        howMuchImg = Int32.Parse(posString[2]);

        if (howMuchImg == 4){
            globalRows = 2;
            globalCol = 2;
            matrix = new int[2,2];
        } else if (howMuchImg == 8){
            globalRows = 2;
            globalCol = 4;
            matrix = new int[2,4];
        } else if (howMuchImg == 9){
            globalRows = 3;
            globalCol = 3;
            matrix = new int[3,3];
        } else if (howMuchImg == 16){
            globalRows = 4;
            globalCol = 4;
            matrix = new int[4,4];
        } else if (howMuchImg == 25){
            globalRows = 5;
            globalCol = 5;
            matrix = new int[5,5];
        }

        // crea lista con las generaciones

        geneticString = posString[1];
        genList = divString(geneticString, "#");


        // crea la matriz desordenada 

        string[] rows = divString(posString[0], "/");

        for (int row = 0; row < matrix.GetLength(0); row++)
        {
            string rowString = rows[row];
            string[] colString = divString(rowString, "-");
            // leer columnas
            for (int col = 0; col < matrix.GetLength(1); col++)
            {
                string num = colString[col];
                if (num != ""){
                    matrix[row, col] = Int32.Parse(num);
                }
                
            }
        }

        for (int k = 0; k < genList.Length-1; k++)
        {
            int[,] nextMatrix = DeepCopy(matrix);

            if(currentGen < genList.Length-1){
                int[,] tmp = apply_chain(divString(genList[currentGen], "@") , nextMatrix);
                resultMatrices.Add(nextMatrix);
                currentGen++;
            
            } else{
                Debug.Log("FUERA DEL INDICE");
            }
        }
        currentGen = -1;

        slider.minValue = 0;
        slider.maxValue = resultMatrices.Count-1;
        slider.wholeNumbers = true;

        updateImages(howMuchImg, matrix);


    }

    void Update()
    {
        updateImages(howMuchImg, resultMatrices[(int)mySlider.value]);
        
    }

    void updateImages(int divNumber, int[,] matrix_)
    {
        int pointer = 0;
        for (int row = 0; row < matrix_.GetLength(0); row++)
        {
            // leer columnas
            for (int col = 0; col < matrix_.GetLength(1); col++)
            {

                int num = matrix_[row, col];

                if (divNumber == 4)
                {
                    if (pointer == 0)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image0.texture = www.texture;
                    } 
                    else  if (pointer == 1)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image1.texture = www.texture;
                        
                    } 
                    else  if (pointer == 2)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image5.texture = www.texture;
                        
                    } 
                    else  if (pointer == 3)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image6.texture = www.texture;
                        
                    }
                    pointer++;
                }


                if (divNumber == 8)
                {
                    if (pointer == 0)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image0.texture = www.texture;
                        
                    } 
                    else  if (pointer == 1)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image1.texture = www.texture;
                        
                    } 
                    else  if (pointer == 2)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image2.texture = www.texture;
                        
                    } 
                    else  if (pointer == 3)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image3.texture = www.texture;
                        
                    }
                    else if (pointer == 4)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image5.texture = www.texture;
                        
                    } 
                    else  if (pointer == 5)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image6.texture = www.texture;
                        
                    } 
                    else  if (pointer == 6)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image7.texture = www.texture;
                        
                    } 
                    else  if (pointer == 7)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image8.texture = www.texture;
                        
                    }
                    pointer++;

                }


                if (divNumber == 9)
                {
                    if (pointer == 0)
                    {
                    WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                    image0.texture = www.texture;
                    
                    } 
                    else  if (pointer == 1)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image1.texture = www.texture;
                        
                    } 
                    else  if (pointer == 2)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image2.texture = www.texture;
                        
                    } 
                    else  if (pointer == 3)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image5.texture = www.texture;
                        
                    }
                    else if (pointer == 4)
                    {
                    WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                    image6.texture = www.texture;
                    
                    } 
                    else  if (pointer == 5)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image7.texture = www.texture;
                        
                    } 
                    else  if (pointer == 6)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image10.texture = www.texture;
                        
                    } 
                    else  if (pointer == 7)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image11.texture = www.texture;
                        
                    }
                    else  if (pointer == 8)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image12.texture = www.texture;
                        
                    }
                    pointer++;

                }
                if (divNumber == 16)
                {
                    if (pointer == 0)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image0.texture = www.texture;
                        
                    } 
                    else  if (pointer == 1)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image1.texture = www.texture;
                        
                    } 
                    else  if (pointer == 2)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image2.texture = www.texture;
                        
                    } 
                    else  if (pointer == 3)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image3.texture = www.texture;
                        
                    }
                    else if (pointer == 4)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image5.texture = www.texture;
                        
                    } 
                    else  if (pointer == 5)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image6.texture = www.texture;
                        
                    } 
                    else  if (pointer == 6)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image7.texture = www.texture;
                        
                    } 
                    else  if (pointer == 7)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image8.texture = www.texture;
                        
                    }
                    else  if (pointer == 8)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image10.texture = www.texture;
                        
                    }
                    else if (pointer == 9)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image11.texture = www.texture;
                        
                    } 
                    else  if (pointer == 10)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image12.texture = www.texture;
                        
                    } 
                    else  if (pointer == 11)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image13.texture = www.texture;
                        
                    } 
                    else  if (pointer == 12)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image15.texture = www.texture;
                        
                    }
                    else if (pointer == 13)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image16.texture = www.texture;
                        
                    } 
                    else  if (pointer == 14)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image17.texture = www.texture;
                        
                    } 
                    else  if (pointer == 15)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image18.texture = www.texture;
                        
                    } 
                    pointer++;

                }
                if (divNumber == 25)
                {
                    if (pointer == 0)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image0.texture = www.texture;
                        
                    } 
                    else  if (pointer == 1)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image1.texture = www.texture;
                        
                    } 
                    else  if (pointer == 2)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image2.texture = www.texture;
                        
                    } 
                    else  if (pointer == 3)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image3.texture = www.texture;
                        
                    }
                    else if (pointer == 4)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image4.texture = www.texture;
                        
                    } 
                    else  if (pointer == 5)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image5.texture = www.texture;
                        
                    } 
                    else  if (pointer == 6)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image6.texture = www.texture;
                        
                    } 
                    else  if (pointer == 7)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image7.texture = www.texture;
                        
                    }
                    else  if (pointer == 8)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image8.texture = www.texture;
                        
                    }
                    else if (pointer == 9)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image9.texture = www.texture;
                        
                    } 
                    else  if (pointer == 10)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image10.texture = www.texture;
                        
                    } 
                    else  if (pointer == 11)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image11.texture = www.texture;
                        
                    } 
                    else  if (pointer == 12)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image12.texture = www.texture;
                        
                    }
                    else if (pointer == 13)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image13.texture = www.texture;
                        
                    } 
                    else  if (pointer == 14)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image14.texture = www.texture;
                        
                    } 
                    else  if (pointer == 15)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image15.texture = www.texture;
                        
                    } 
                    else  if (pointer == 16)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image16.texture = www.texture;
                        
                    }
                    else  if (pointer == 17)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image17.texture = www.texture;
                        
                    }
                    else if (pointer == 18)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image18.texture = www.texture;
                        
                    } 
                    else  if (pointer == 19)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image19.texture = www.texture;
                        
                    } 
                    else  if (pointer == 20)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image20.texture = www.texture;
                        
                    } 
                    else  if (pointer == 21)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image21.texture = www.texture;
                        
                    }
                    else if (pointer == 22)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image22.texture = www.texture;
                        
                    } 
                    else  if (pointer == 23)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image23.texture = www.texture;
                        
                    } 
                    else  if (pointer == 24)
                    {
                        WWW www = new WWW("file:///" + "/home/ignacio/Datos2/Lets-play/Server/blocksFolder/" + num + ".png");
                        image24.texture = www.texture;
                        
                    } 
                    pointer++;

                }
            }
        }
        
        
    }


}
