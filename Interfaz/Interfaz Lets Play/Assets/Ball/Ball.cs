using System;
using System.Collections;
using System.Collections.Generic;
using Client;
using UnityEngine;
using UnityEngine.UI;
using Field;
using UnityEngine.SceneManagement;

public class Ball : MonoBehaviour
{
    private bool flag = true;
    private bool J1flag = true;
    private bool J2flag = false;
    private float _timeJ2;
    private Vector3 _launchPosition;
    private LineRenderer _lineRenderer;
    private Rigidbody2D _rigidbody2D;
    private Animator _animator;
    private int _pointsJ1;
    private int _pointsJ2;
    [SerializeField] private GameObject starParticule;
    [SerializeField] private Text goalsJ1;
    [SerializeField] private Text goalsJ2;

    private void Awake()
    {
        _animator = GetComponent<Animator>();
        _rigidbody2D = GetComponent<Rigidbody2D>();
        _lineRenderer = GetComponent<LineRenderer>();
    }

    private void Update()
    {
        if (transform.position.x  < -11)
        {
            _pointsJ2 += 1;
            string message = parseJson("BP", "J2", "goal" , "");
            SocketClient.StartClient(message);
            string messageR = SocketClient.MessageR;
            Debug.Log(messageR);
            if (messageR[0] == 'L')
            {
                SceneManager.LoadScene("BP Lose");
            }
            else
            {
                goalsJ1.text = _pointsJ2.ToString();
                Instantiate(starParticule, transform.position, Quaternion.identity);
                Vector3 origin = new Vector3(0, 0);
                transform.position = origin;
                _rigidbody2D.velocity = origin;
            }
            
        }
        else if (transform.position.x > 11)
        {
            _pointsJ1 += 1;
            string message = parseJson("BP", "J1", "goal", "");
            SocketClient.StartClient(message);
            string messageR = SocketClient.MessageR;
            Debug.Log(messageR);
            if (messageR[0] == 'W')
            {
                SceneManager.LoadScene("BP Win");
            }
            else
            {
                goalsJ2.text = _pointsJ1.ToString();
                Instantiate(starParticule, transform.position, Quaternion.identity);
                Vector3 origin = new Vector3(0, 0);
                transform.position = origin;
                _rigidbody2D.velocity = origin;
            }
            
        }
        
        _lineRenderer.SetPosition(0, _launchPosition);
        _lineRenderer.SetPosition(1, transform.position);
        if (_rigidbody2D.velocity.magnitude <= 0.1)
        {
            _animator.enabled = false;
            
            if (flag)
            {
                
                if (J1flag)
                {
                    
                    string column = (((int)transform.position.x +9)/2).ToString();
                    string row = (((int)transform.position.y -4)/-2).ToString();
                    if (Int32.Parse(column) < 0) { column = "0"; }
                    if (Int32.Parse(column) > 9) { column = "9"; }
                    if (Int32.Parse(row) < 0) { row = "0"; }
                    if (Int32.Parse(row) > 4) { row  = "4"; }
                    string message = parseJson("BP", "J1", row+column , "");
                    SocketClient.StartClient(message);
                    Debug.Log(message);
                    Debug.Log(SocketClient.MessageR);
                    Field.Field.UpdatePath(transform.position);
                    flag = false;
                }

                if (J2flag)
                {
                    
                    string column = (((int)transform.position.x +9)/2).ToString();
                    string row = (((int)transform.position.y -4)/-2).ToString();
                    if (Int32.Parse(column) < 0) { column = "0"; }
                    if (Int32.Parse(column) > 9) { column = "9"; }
                    if (Int32.Parse(row) < 0) { row = "0"; }
                    if (Int32.Parse(row) > 4) { row  = "4"; }
                    string message = parseJson("BP", "J2", row+column , "");
                    SocketClient.StartClient(message);
                    Field.Field.UpdatePath(transform.position);
                    flag = false;
                }
            }

            if (J2flag)
            {
                _timeJ2 += Time.deltaTime;
                if (_timeJ2 > 3)
                {
                    J2flag = false;
                    J1flag = true;
                    string direction = SocketClient.MessageR;
                    int x;
                    int y;
                    if (direction.Length > 4)
                    {
                        x = Int32.Parse(direction[4].ToString());
                        y = Int32.Parse(direction[3].ToString());
                    }
                    else
                    {
                        x = Int32.Parse(direction[1].ToString());
                        y = Int32.Parse(direction[0].ToString());
                    }
                    Vector3 directionToPositionIA = new Vector3(-9 + 2 * x, 4 - 2 * y);
                    Vector2 directionToPosition = directionToPositionIA-transform.position;
                    _rigidbody2D.AddForce( directionToPosition * 250);
                    _timeJ2 = 0;
                }
            }
        }
        else
        {
            flag = true;
            _animator.enabled = true;
        }
    }
    private void OnMouseDown()
    {
        if (_rigidbody2D.velocity.magnitude <= 0.1 && J1flag)
        {
            GetComponent<LineRenderer>().enabled = true;
        }
    }
    private void OnMouseUp()
    {
        if (_rigidbody2D.velocity.magnitude <= 0.1 && J1flag)
        {
            Vector2 directionToPosition = transform.position - _launchPosition;
            _rigidbody2D.AddForce(directionToPosition * 250);
            _lineRenderer.enabled= false;
            J1flag = false;
            J2flag = true;
        }
    }
    
    private void OnMouseDrag()
    {
        
        if (_rigidbody2D.velocity.magnitude <= 0.1 && J1flag)
        {
            Vector3 newPosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            _launchPosition = new Vector3(newPosition.x, newPosition.y);
            if (transform.position.x - _launchPosition.x <= -3)
            {
                _launchPosition.x = newPosition.x + ((transform.position.x - _launchPosition.x) + 3);
            }

            if (transform.position.x - _launchPosition.x >= 3)
            {
                _launchPosition.x = newPosition.x + ((transform.position.x - _launchPosition.x) - 3);
            }

            if (transform.position.y - _launchPosition.y <= -3)
            {
                _launchPosition.y = newPosition.y + ((transform.position.y - _launchPosition.y) + 3);
            }

            if (transform.position.y - _launchPosition.y >= 3)
            {
                _launchPosition.y = newPosition.y + ((transform.position.y - _launchPosition.y) - 3);
            }
        }
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
    
    int HowMany(string input)
    {
        int count = 0;
        for (int i = 3; i < input.Length; i++)
            if (input[i] == '$')
            {
                count += 1;
            }
        return count;
    }

    void Createlines()
    {
        int limit = HowMany(SocketClient.MessageR);
        _lineRenderer.positionCount = limit + 2;
        string positionS = "";
        int j = 2;
        for (int i = 3; i < SocketClient.MessageR.Length; i++)
        {
            if (SocketClient.MessageR[i] == '$')
            {
                int positionI = Int32.Parse(positionS);
                int y = 0;
                int x = positionI % 10;
                if (x != positionI)
                {
                    y = positionI / 10;
                }

                Debug.Log(x);
                Debug.Log(y);
                Vector3 _nextNodePosition = new Vector3(-9 + 2 * x, 4 - 2 * y);
                _lineRenderer.SetPosition(j, _nextNodePosition);
                positionS = "";
                j++;
            }
            else
            {
                positionS += SocketClient.MessageR[i];
            }
        }
    }
}

