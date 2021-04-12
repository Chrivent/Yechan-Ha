using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class JombieMaker : MonoBehaviour
{
    public GameObject JombiePrefab;                                 // 생성할 좀비의 원본 prefab
    public List<GameObject> ZombiePool = new List<GameObject>();    // 좀비 오브젝트 풀
    private int JombieCount = 20;
    public int JombieIndex = 0;
    private float DieCnt = 0;
    public float makerRateMin =15f;                                 // 좀비 최소 생성 주기
    public float makerRateMax = 25.0f;                              // 좀비 최대 생성 주기
    private float makerRate;                                        // 좀비 생성 주기
    private float timeAfterMake;                                    // 최근 생성 후 경과 시간 
    public Text ScoreText;
    void Awake()
    {
        CreatePooling();
    }
    // obj pool create
    void CreatePooling()
    {
        // 부모 오브젝트 생성 
        GameObject objPools = new GameObject("zombieObjectPools");
        // 좀비를 미리 만들어둔다
        for (int i = 0; i < JombieCount; i++)
        {
            float ranX = Random.Range(0f, 15f);
            var obj = Instantiate<GameObject>(JombiePrefab, new Vector3(ranX, 3f, 0f), Quaternion.identity);
            obj.name = i.ToString();
            obj.SetActive(false);
            ZombiePool.Add(obj);
        }
    }
    public GameObject GetZombie()
    {
        for (int i = 0; i < ZombiePool.Count; i++)
        {
            //사용가능한 좀비를 뱉어낸다
            if (ZombiePool[i].activeSelf == false)
            {
                return ZombiePool[i];
            }
        }
        return null;    // 사용가능한거없으면 null
    }
    // Start is called before the first frame update
    void Start()
    {
        timeAfterMake = 0f;                                         // 누적시간 0으로 초기화
        makerRate = Random.Range(makerRateMin, makerRateMax);       // 좀비 생성 주기를 random으로 설정
        ScoreText.text = "Score : " + DieCnt + " 점";
    }

    // Update is called once per frame
    void Update()
    {
        timeAfterMake += Time.deltaTime;

        if(timeAfterMake >= makerRate)
        {
            // 누적된 시간 리셋
            timeAfterMake = 0f;
            
            
            if(JombieIndex <20)
            {
                ZombiePool[JombieIndex].gameObject.SetActive(true);
                JombieIndex++;
            }
            if(JombieIndex==20)
            {
                
                for(int i=0;i<ZombiePool.Count;i++)
                {
                    if (ZombiePool[i].activeSelf == false)
                        DieCnt++;

                    //Debug.Log("현재 죽은 좀비의 수 : " + DieCnt);
                    
                }
                if (DieCnt > 19)
                {
                    GameManager gManager = FindObjectOfType<GameManager>();
                    gManager.Win();
                }
                else
                    DieCnt = 0;
            }
            //if (JombieCount != 0)
            //{
            //    GameObject Jombie
            //      = Instantiate(JombiePrefab, new Vector3(ranX, 3f, 0f), Quaternion.identity);
            //    JombieCount--;
            //}
            
            makerRate = Random.Range(makerRateMin, makerRateMax);
        }
    }
}
