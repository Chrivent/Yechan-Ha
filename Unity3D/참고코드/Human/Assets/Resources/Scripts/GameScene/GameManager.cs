using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement; // Scene관련 라이브러리
public class GameManager : MonoBehaviour
{
    public GameObject gameoverText;
    public GameObject winText;

    private bool isGameWin;
    private bool isGameover;
    // Start is called before the first frame update
    void Start()
    {
        isGameover = false;
        isGameWin = false;
    }

    // Update is called once per frame
    void Update()
    {
        if(isGameWin)
        {
            winText.SetActive(true);
            if (Input.GetKeyDown(KeyCode.R))
            {
                SceneManager.LoadScene("TitleScene");
            }
        }
        if(isGameover)
        {
            if(Input.GetKeyDown(KeyCode.R))
            {
                SceneManager.LoadScene("TitleScene");
            }
        }
    }
    public void Win()
    {
        isGameWin = true;

    }
    public void EndGame()
    {
        isGameover = true;

        gameoverText.SetActive(true);

    }
}
