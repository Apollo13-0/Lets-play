using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Client;
using UnityEditor.SearchService;
using UnityEngine.SceneManagement;


public class ButtonBPGame : MonoBehaviour
{
    public Button ButtonStart;
    public InputField Score;
    public InputField Players;
    private string message;

    void Start()
    {
        Button btn = ButtonStart.GetComponent<Button>();
        btn.onClick.AddListener(TaskOnClick);
    }

    void TaskOnClick()
    {
        parseJson("BP", "Config", Score.text, Players.text);
        //message = "BP$" + Score.text + "$" + Players.text;
        Debug.Log(message);
        SocketClient.StartClient(message);
        SceneManager.LoadScene("BP Game");
        Debug.Log("You have clicked the button!");
    }

    void parseJson(string game,string key,string info1, string info2)
    {
        message = "{" +
                  "\"Game\":" + "\"" + game + "\"" + "," +
                  "\"Key\":" + "\"" + key + "\"" + "," +
                  "\"Info1\":" + "\"" + info1 + "\"" + "," +
                  "\"Info2\":" + "\"" + info2 + "\"" + "}";
    }
}
