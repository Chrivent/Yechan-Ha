using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public GameObject gameover;
    public Text timeText;
    public Text Score;
        
    private float surviveTime;
    private bool isGameOver;

    // Start is called before the first frame update
    void Start()
    {
        isGameOver = false;
        surviveTime = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (!isGameOver)
        {
            surviveTime += Time.deltaTime;
            timeText.text = "Time : " + (int)surviveTime;
        }
        else
        {
            if (Input.GetKeyDown(KeyCode.R))
                SceneManager.LoadScene("TitleScene");
        }
    }
    public void EndGame()
    {
        isGameOver = true;

        gameover.SetActive(true);

        float bestTime = PlayerPrefs.GetFloat("BestTime");

        if(surviveTime > bestTime)
        {
            bestTime = surviveTime;
            PlayerPrefs.SetFloat("BestTime", bestTime);
        }

        Score.text = "BestTime :" + (int)bestTime;
    }
}
