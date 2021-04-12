using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Enemy : MonoBehaviour
{
    public Transform target;
    private float speed = 0.4f;
    private Rigidbody myRigidbody;
    public Slider HPbar;
    public Transform HPbarTr;
    // Start is called before the first frame update
    void Start()
    {
        myRigidbody = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        // enemy들을 따라서 움직이는 HPbar
        HPbar.transform.position = HPbarTr.position;
        HPbar.transform.rotation = HPbarTr.rotation;

        // Enemy의 이동
        myRigidbody.transform.Translate(transform.forward * speed * Time.deltaTime, Space.World);
        transform.LookAt(target);
    }
}
