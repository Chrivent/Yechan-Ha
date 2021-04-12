using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class Gate : MonoBehaviour
{
    public GameObject DunSelect;
    private Animator GateAnimator; // 플레이어 캐릭터의 애니메이터
    // Start is called before the first frame update
    void Start()
    {
        GateAnimator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.tag == "Player")
        {
            StartCoroutine(DoorOpeneffect());
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if(other.tag == "Player")
        {
            StartCoroutine(DoorCloseeffect());
        }
    }

    private IEnumerator DoorCloseeffect()
    {
        GateAnimator.SetBool("Open", false);
        yield return new WaitForSeconds(0.3f);
        DunSelect.SetActive(false);
    }
    private IEnumerator DoorOpeneffect()
    {
        GateAnimator.SetBool("Open", true);
        yield return new WaitForSeconds(0.3f);
        DunSelect.SetActive(true);
        //SceneManager.LoadScene("Dungeon");
    }
}
