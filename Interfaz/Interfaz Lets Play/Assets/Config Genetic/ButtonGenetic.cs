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


namespace ButtonGenetic
{
    public class ButtonGenetic : MonoBehaviour
    {
        public InputField divisionNumber;

        private string path;

        private string message;

        public RawImage image;


        public void playGenetic()
        {
            if (Int32.Parse(divisionNumber.text) > 2)
            {
                if (IsPowerOfTwo(Convert.ToUInt64(divisionNumber.text)) || isSquare(Int32.Parse(divisionNumber.text))) 
                {
                    OpenExplorer();
                    if (path != null)
                    {
                        changeScene();
                    }
                    else
                    {
                        Debug.Log("no hay path");
                    }
                    
                } else 
                {
                    Debug.Log("no es numero de div valido");
                }
            }
            else 
            {
                Debug.Log("no es numero de div valido == 0,1,2");
            }
            

        }

        void changeScene()
        {
            string message = parseJson("Genetic", "Config", divisionNumber.text, path);
            Debug.Log(message);
            SocketClient.StartClient(message);
            string messageR = SocketClient.MessageR;

            SceneManager.LoadScene("GeneticPuzzle");
        }

        string parseJson(string game,string key,string info1, string info2)
        {
            string message = "{" +
                    "\"Game\":" + "\"" + game + "\"" + "," +
                    "\"Key\":" + "\"" + key + "\"" + "," +
                    "\"Info1\":" + "\"" + info1 + "\"" + "," +
                    "\"Info2\":" + "\"" + info2 + "\"" + "}";
            return message;
        }

        public void OpenExplorer()
        {
            path = EditorUtility.OpenFilePanel("Select png","","png");
            Debug.Log(path);
            //GetImage();
        }

        void GetImage()
        {
            if (path != null)
            {
                UpdateImage();
            }
        }

        void UpdateImage()
        {
            WWW www = new WWW("file:///" + path);
            image.texture = www.texture;

        }

        bool IsPowerOfTwo(ulong x)
        {
            return (x != 0) && ((x & (x - 1)) == 0);
        }

        static bool isSquare(int n)
        {
            double result = Math.Sqrt(n);
            return result%1 == 0;
        }
    }
}



