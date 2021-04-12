using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Pause : MonoBehaviour
{
    private bool IsPause;
    // Start is called before the first frame update
    void Start()
    {
        IsPause = false;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void CheckPause()
    {
        if (IsPause)
            IsPause = false;
        else
            IsPause = true;

        if (IsPause)
            Time.timeScale = 0;
        else
            Time.timeScale = 1;
    }
}
