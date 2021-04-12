using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using LitJson;
using System.IO;

public class Item
{
    public int ID;          //
    public string Name;
    public string Dis;

    public Item(int id, string name, string dis)
    {
        ID = id;
        Name = name;
        Dis = dis;
    }
}

public class JsonMgr : MonoBehaviour
{
    public List<Item> ItemList = new List<Item>();

    // Start is called before the first frame update
    void Start()
    {
        ItemList.Add(new Item(0, "검", "검이다"));
        ItemList.Add(new Item(1, "방패", "방패이다"));
        ItemList.Add(new Item(2, "활", "활이다"));
        ItemList.Add(new Item(3, "포션", "포션이다"));
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Save()
    {
        Debug.Log("저장한다!");

        JsonData ItemJson = JsonMapper.ToJson(ItemList);

        File.WriteAllText(Application.dataPath
                                + "/ItemData.json"
                                , ItemJson.ToString());
    }

    public void Load()
    {
        Debug.Log("불러온다");

        string Jsonstring = File.ReadAllText(Application.dataPath
                                + "/Resources/ItemData.json");
        Debug.Log(Jsonstring);

        JsonData itemData = JsonMapper.ToObject(Jsonstring);

        for(int i=0;i<itemData.Count; i++)
        {
            Debug.Log(itemData[i]["ID"].ToString());
            Debug.Log(itemData[i]["Name"].ToString());
            Debug.Log(itemData[i]["Dis"].ToString());
        }
    }
}
