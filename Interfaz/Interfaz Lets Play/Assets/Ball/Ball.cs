using System;
using System.Collections;
using System.Collections.Generic;
using Client;
using UnityEngine;
using UnityEngine.UI;
using Field;

public class Ball : MonoBehaviour
{
    private bool flag = true;
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
            _pointsJ1 += 1;
            goalsJ1.text = _pointsJ1.ToString();
            Instantiate(starParticule, transform.position, Quaternion.identity);
            Vector3 origin = new Vector3(0, 0);
            transform.position = origin;
            _rigidbody2D.velocity = origin;
        }
        else if (transform.position.x > 11)
        {
            _pointsJ2 += 1;
            goalsJ2.text = _pointsJ2.ToString();
            Instantiate(starParticule, transform.position, Quaternion.identity);
            Vector3 origin = new Vector3(0, 0);
            transform.position = origin;
            _rigidbody2D.velocity = origin;
        }
        
        _lineRenderer.SetPosition(0, _launchPosition);
        _lineRenderer.SetPosition(1, transform.position);
        if (_rigidbody2D.velocity.magnitude <= 0.1)
        {
            _animator.enabled = false;
            if (flag)
            {
                string column = (((int)transform.position.x +9)/2).ToString();
                string row = (((int)transform.position.y -4)/-2).ToString();
                string message = parseJson("BP", "J1Path", row+column , "");
                SocketClient.StartClient(message);
                flag = false;
                Debug.Log(SocketClient.MessageR);
                Field.Field.UpdatePath(transform.position);
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
        if (_rigidbody2D.velocity.magnitude <= 0.1)
        {
            GetComponent<LineRenderer>().enabled= true;
        }
        
    }
    private void OnMouseUp()
    {
        if (_rigidbody2D.velocity.magnitude <= 0.1)
        {
            Vector2 directionToPosition = transform.position - _launchPosition;
            _rigidbody2D.AddForce(directionToPosition * 250);
            _lineRenderer.enabled= false;
        }
    }
    
    private void OnMouseDrag()
    {
        if (_rigidbody2D.velocity.magnitude <= 0.1)
        {
            Vector3 newPosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            _launchPosition = new Vector3(newPosition.x, newPosition.y);
            if (transform.position.x - _launchPosition.x <= -3)
            {
                _launchPosition.x = newPosition.x +((transform.position.x - _launchPosition.x) + 3);
            }
            if (transform.position.x - _launchPosition.x >= 3)
            {
                _launchPosition.x = newPosition.x +((transform.position.x - _launchPosition.x) - 3);
            }
            if (transform.position.y - _launchPosition.y <= -3)
            {
                _launchPosition.y = newPosition.y +((transform.position.y - _launchPosition.y) + 3);
            }
            if (transform.position.y - _launchPosition.y >= 3)
            {
                _launchPosition.y = newPosition.y +((transform.position.y - _launchPosition.y) - 3);
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
                Debug.Log(x);
                Debug.Log(y);
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

