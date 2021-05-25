using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = System.Random;
using Client;
namespace Field
{
    public class Field : MonoBehaviour
    {
        private static LineRenderer _lineRenderer;
        [SerializeField] private GameObject _obstaculeP1Prefab;
        [SerializeField] private GameObject _obstaculeP2Prefab;
        void Awake()
        {
            _lineRenderer = GetComponent<LineRenderer>();
            int j=0;
            Debug.Log(SocketClient.MessageR);
            for (int i = 0; i < SocketClient.MessageR.Length-1;)
            {
                string m= SocketClient.MessageR[i].ToString();
                string n = SocketClient.MessageR[i+1].ToString();
                int row = Int32.Parse(m);
                int column = Int32.Parse(n);
                Vector3 position = new Vector3(-9 + 2 * column, 4 - 2 * row);
                i+=2;
                if (j % 2 != 0)
                {
                    Instantiate(_obstaculeP1Prefab, position, Quaternion.identity);
                }
                else
                {
                    Instantiate(_obstaculeP2Prefab, position, Quaternion.identity);
                } 
                j++;
            }
        }
        static int HowMany(string input)
        {
            int count = 0;
            for (int i = 3; i < input.Length; i++)
                if (input[i] == '$')
                {
                    count += 1;
                }
            return count;
        }

        public static void UpdatePath()
        {
            int limit = HowMany(SocketClient.MessageR);
            _lineRenderer.positionCount = limit+2;
            string positionS="";
            int j=2;
            for (int i=3; i < SocketClient.MessageR.Length; i++)
            {
                if (SocketClient.MessageR[i] == '$')
                {
                    int positionI = Int32.Parse(positionS);
                    int y = 0;
                    int x= positionI%10;
                    if (x != positionI){
                        y = positionI/10;
                    }
                    Vector3 _nextNodePosition = new Vector3(-9 + 2 * x, 4 - 2 * y);
                    _lineRenderer.SetPosition(j, _nextNodePosition);
                    positionS="";
                    j++;
                }
                else
                {
                    positionS += SocketClient.MessageR[i];
                }
            }
        }
    }
    
}
