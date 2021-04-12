using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Jombie : MonoBehaviour
{
    public Rigidbody jombieRigidbody;
    public float speed = 0.2f;
    private Transform target;                                       // 추적 대상
 
    // Start is called before the first frame update
    void Start()
    {
      
        jombieRigidbody = GetComponent<Rigidbody>();
        target = FindObjectOfType<PlayerController>().transform;    // target을 설정한다.
    }

    // Update is called once per frame
    void Update()
    {
         // 애가 자꾸 따라가게해야하니까 speed * deltatime * 0.5
        jombieRigidbody.transform.Translate(transform.forward*speed*Time.deltaTime , Space.World);
        transform.LookAt(target);                                    // 좀비의 타겟을 업데이트
    }
  
    public void Die()
    {
        gameObject.SetActive(false);
        
    }
}
