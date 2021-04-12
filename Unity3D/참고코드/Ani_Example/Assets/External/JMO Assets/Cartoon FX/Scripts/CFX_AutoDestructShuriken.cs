using UnityEngine;
using System.Collections;

// Cartoon FX  - (c) 2015 Jean Moreno

// Automatically destructs an object when it has stopped emitting particles and when they have all disappeared from the screen.
// Check is performed every 0.5 seconds to not query the particle system's state every frame.
// (only deactivates the object if the OnlyDeactivate flag is set, automatically used with CFX Spawn System)

[RequireComponent(typeof(ParticleSystem))]
public class CFX_AutoDestructShuriken : MonoBehaviour
{
	// If true, deactivate the object instead of destroying it
	public bool OnlyDeactivate;
   	
	void OnEnable()
	{
		StartCoroutine("CheckIfAlive");
	}
	
	IEnumerator CheckIfAlive ()
	{
		ParticleSystem ps = this.GetComponent<ParticleSystem>();
		
		while(true && ps != null)
		{
			yield return new WaitForSeconds(0.5f);
			if(!ps.IsAlive(true))
			{
                if (OnlyDeactivate)
                {
#if UNITY_3_5
						this.gameObject.SetActiveRecursively(false);
#else
                    //수정 부분
                    //gameObject.SetActive(false);
                    if (transform.parent != null && transform.parent.name != "EffectPool")
                        transform.parent.gameObject.SetActive(false);
                    else
                        gameObject.SetActive(false);
#endif
                }
                else
					GameObject.Destroy(this.gameObject);
				break;
			}
		}
	}

    /////////////////////////
    //이 밑은 추가 작업한 부분.
    /////////////////////////

    public bool flip = false;

    public void set_flip(bool is_flip)
    {
        flip = is_flip;
        transform.rotation = Quaternion.identity;

        if (flip)
        {
            transform.localRotation = Quaternion.Euler(new Vector3(-45.0f, 180.0f, 0.0f));
        }
        else
        {
            transform.localRotation = Quaternion.Euler(new Vector3(45.0f, 0.0f, 0.0f));
        }

    }
}
