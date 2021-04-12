using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour
{
    public Rigidbody playerRigidbody;
    public float speed = 8f;

    [Header("object pool")]
    public GameObject BulletPrefab;
    public int maxBullet;
    public List<GameObject> BulletPool = new List<GameObject>();

    public GameObject Gun;


    public int HP;
    public Slider HPbar;
    public Text Hptext;

    void Awake()
    {
        maxBullet = 10;
        CreatePooling();
    }

    public void CreatePooling()
    {
        // 부모 오브젝트 생성 
        GameObject objPools = new GameObject("ObjectPools");
        // 총알을 미리 만들어둔다
        for(int i=0;i<maxBullet;i++)
        {
            var obj = Instantiate<GameObject>(BulletPrefab, Gun.transform.position, Gun.transform.rotation);
            obj.name = i.ToString();
            obj.SetActive(false);
            BulletPool.Add(obj);
        }
    }
 
    public GameObject GetBullet()
    {
        for(int i=0;i<BulletPool.Count;i++)
        {
            //사용가능한 총알을 뱉어낸다
            if(BulletPool[i].activeSelf == false)
            {
                return BulletPool[i];
            }
        }
        return null;    // 사용가능한거없으면 null
    }
    // Start is called before the first frame update
    void Start()
    {
        playerRigidbody = GetComponent<Rigidbody>();
        Gun = transform.Find("Gun2").gameObject;
        HP = 100;                                       // 플레이어의 체력 값
    }

    // Update is called once per frame
    void Update()
    {
        float xInput = Input.GetAxis("Horizontal");
        float zInput = Input.GetAxis("Vertical");

        float xSpeed = xInput * speed;
        float zSpeed = zInput * speed;

        Vector3 moveVelocity = new Vector3(xSpeed, 0f, zSpeed);
        playerRigidbody.velocity = moveVelocity;
        //q키 눌려서 회전시켜서 뒤에 애도 공격 
        if (Input.GetKey(KeyCode.Q))
            transform.Rotate(Vector3.up, -10, Space.World);
        if (Input.GetKey(KeyCode.E))
            transform.Rotate(Vector3.up, 10, Space.World);

        if(Input.GetKeyDown(KeyCode.Space))
        {
            if (GetBullet() != null)
            {
                GetBullet().transform.position = Gun.transform.position;
                GetBullet().transform.rotation = Gun.transform.rotation;
                GetBullet().gameObject.SetActive(true);
            }
            //GameObject Bullet
            //    = Instantiate(BulletPrefab, Gun.transform.position, Gun.transform.rotation);
        }
        
     
    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Jombie")
        {
            HP--;
            if (HP == 0)
                Die();
            // 체력바 및 텍스트 출력
        HPbar.value = (float)HP;
        Hptext.text = HP.ToString() + "/100";
        }
    }
    public void Die()
    {
        gameObject.SetActive(false);

        GameManager gManager = FindObjectOfType<GameManager>();

        gManager.EndGame();

    }
}
