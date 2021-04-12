using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneChanger : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    // Loading MakeScene
    public void LoadMakeScene()
    {
        SceneManager.LoadScene("MakeScene");
    }
    // Loading TownScene
    public void LoadTownScene()
    {
        SceneManager.LoadScene("TownScene");
    }
    // Loading DungeonScene
    public void LoadDungeonScene()
    {
        SceneManager.LoadScene("DungeonScene");
    }

}
