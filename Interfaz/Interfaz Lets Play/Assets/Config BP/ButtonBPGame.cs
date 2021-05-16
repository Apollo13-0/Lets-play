using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Client;


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
        message = "{" +
                  " \"Config\":" + "\"BP\"," +
                  "\"Score\":" + "\"" + Score.text + "\"" + "," +
                  "\"Players\":" + "\"" + Players.text + "\"" + "}";
        //message = "BP$" + Score.text + "$" + Players.text;
        Debug.Log(message);
        SocketClient.StartClient(message);
        Debug.Log("You have clicked the button!");
    }
}
