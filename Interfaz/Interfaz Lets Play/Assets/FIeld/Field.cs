using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = System.Random;

public class Field : MonoBehaviour
{

    [SerializeField] private GameObject _obstaculeP1Prefab;
    [SerializeField] private GameObject _obstaculeP2Prefab;
    void Awake()
    {
        Random rnd = new Random();
        for (int i = 0; i < 10;)
        {
            if (i % 2 != 0)
            {
                int n = rnd.Next(5);
                int m = rnd.Next(10);
                Vector3 position = new Vector3(-9 + 2 * m, 4 - 2 * n);
                Instantiate(_obstaculeP1Prefab, position, Quaternion.identity);
                ++i;
            }
            else
            {
                int n = rnd.Next(5);
                int m = rnd.Next(10);
                Vector3 position = new Vector3(-9 + 2 * m, 4 - 2 * n);
                Instantiate(_obstaculeP2Prefab, position, Quaternion.identity);
                ++i;
            }

        }
    }
    
}
