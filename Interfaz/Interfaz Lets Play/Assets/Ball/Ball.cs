using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ball : MonoBehaviour
{
    private Vector3 _launchPosition;

    private void Update()
    {
        GetComponent<LineRenderer>().SetPosition(0, _launchPosition);
        GetComponent<LineRenderer>().SetPosition(1, transform.position);
    }
    private void OnMouseDown()
    {
        GetComponent<LineRenderer>().enabled= true;
    }
    private void OnMouseUp()
    {
        Vector2 directionToPosition = transform.position - _launchPosition;
        GetComponent<Rigidbody2D>().AddForce(directionToPosition * 250);
        GetComponent<LineRenderer>().enabled= false;
    }
    
    private void OnMouseDrag()
    {
        Vector3 newPosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        _launchPosition = new Vector3(newPosition.x, newPosition.y);
    }
}

