using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Ball : MonoBehaviour
{
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
        }
        else
        {
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
}

