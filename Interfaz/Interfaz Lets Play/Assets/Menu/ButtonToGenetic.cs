using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class ButtonToGenetic : MonoBehaviour
{
    public Button ButtonToStart;
    // Start is called before the first frame update
    void Start()
    {
        Button btn = ButtonToStart.GetComponent<Button>();
        btn.onClick.AddListener(TaskOnClick);
    }

    void TaskOnClick()
    {
        Debug.Log("Welcome to Genetic Puzzle");
        SceneManager.LoadScene("Config Puzzle");
    }
}
