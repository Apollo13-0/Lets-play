using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEditor;
using System.IO;


public class ConfigGenetic : MonoBehaviour
{
    string path;
    public RawImage image;

    public void OpenExplorer()
    {
        path = EditorUtility.OpenFilePanel("Select png","","png");
        GetImage();
    }

    void GetImage()
    {
        if (path != null)
        {
            UpdateImage();
        }
    }

    void UpdateImage()
    {
        WWW www = new WWW("file:///" + path);
        image.texture = www.texture;
    }

}
