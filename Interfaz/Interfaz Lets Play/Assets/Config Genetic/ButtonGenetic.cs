using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Client;
using UnityEditor.SearchService;
using UnityEngine.SceneManagement;

public class ButtonGenetic : MonoBehaviour
{
    public InputField divisionNumber;
    //public RawImage image;
    private string message;

    public RawImage image;

    public void playGenetic()
    {
        changeScene();
    }

    void changeScene()
    {
        //parseJson("Genetic", "Config", divisionNumber.text, .text);
        //message = "BP$" + Score.text + "$" + Players.text;
        //Debug.Log(message);
        //SocketClient.StartClient(message);
        SceneManager.LoadScene("GeneticPuzzle");
        Debug.Log(divisionNumber.text + "divisiones ");
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

