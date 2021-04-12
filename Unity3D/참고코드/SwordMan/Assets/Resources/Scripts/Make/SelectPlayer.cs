using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class SelectPlayer : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void MakeSpear()
    {
        
        SceneManager.LoadScene("TownScene");
    }

    public void MakeSword()
    {
        SceneManager.LoadScene("TownScene");
    }
}
