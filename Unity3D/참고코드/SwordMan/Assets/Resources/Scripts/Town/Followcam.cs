using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Followcam : MonoBehaviour
{
    public float y = 0f;

    public  Transform target;           // 카메라가 바라볼 대상
    public float distance = 10.0f;      // 플레이어의 카메라와의 거리
    public float height = 5.0f;         // 플레이어와 카메라 사이의 높이

    private Transform Mytr;             // 내 자신의 Transform 변수
    
    // Start is called before the first frame update
    void Start()
    {
        Mytr = GetComponent<Transform>();
    }

    // Update is called once per frame
    void LateUpdate()
    {
        Mytr.position = target.position - (target.forward * distance) + (Vector3.up * height);
        Mytr.LookAt(target);
    }
    void Update()
    {
       
    }
}
