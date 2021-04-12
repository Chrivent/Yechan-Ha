using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicAttack : MonoBehaviour
{
    public bool Attack { get; private set; } // 값 할당은 내부에서만 가능

    void Awake()
    {
        Attack = false;
    }

    void Update()
    {
        Attack = false; 
    }
    public void AttackOn()
    {
        Attack = true;
    }

    
}
