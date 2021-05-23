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

        [SerializeField] private GameObject _obstaculeP1Prefab;
        [SerializeField] private GameObject _obstaculeP2Prefab;
        void Awake()
        {
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
        
    }
}
