using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    public float speed = 8f;
    private Rigidbody bulletRigidbody;
    public float time;

    // Start is called before the first frame update
    void Start()
    {
        bulletRigidbody = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        bulletRigidbody.transform.Translate(transform.forward, Space.World);

        time += Time.deltaTime;
        if (time >= 2.0f)
        {
            gameObject.SetActive(false);
            time = 0f;
        }
    }
    
    private void OnTriggerEnter(Collider other)
    {
        if(other.tag == "Jombie")
        {
            //PlayerController playerController = other.GetComponent<PlayerController>();
            Jombie jombie = other.GetComponent<Jombie>();
            if (jombie != null)
                jombie.Die();

            gameObject.SetActive(false);
         
        }
    }
}
