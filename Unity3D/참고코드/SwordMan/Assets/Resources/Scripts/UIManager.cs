using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIManager : MonoBehaviour
{
    public static UIManager instance
    {
        get
        {
            if (m_instance == null)
            {
                m_instance = FindObjectOfType<UIManager>();
            }
            return m_instance;
        }
    }

    private static UIManager m_instance;

    public Slider Exp;
    public Text ExpText;

    public Slider HP;
    public Text HPText;

    public Slider MP;
    public Text MPText;

    public Text Level;

    // EXP 업데이트
    public void UpdateExp(float NowExp, float MaxExp)
    {
        // 경험치 값을 퍼센티지로 바꿔준다.
        float ExpToPer = NowExp / MaxExp * 100.0f;
        // 경험치 슬라이더의 값을 바꿔준다.
        Exp.value = ExpToPer;
        // 경험치 슬라이더 텍스트의 내용을 바꿔준다.
        ExpText.text = ExpToPer.ToString() + " / 100 %";
    }
    // HP 업데이트
    public void UpdateHP(int NowHP, int MaxHP)
    {
        // HP값을 퍼센티지로 바꿔준다.
        float HPToPer = NowHP / MaxHP * 100.0f;
        // HP 슬라이더의 값을 바꿔준다.
        HP.value = HPToPer;
        // HP 슬라이더 텍스트의 내용을 바꿔준다.
        HPText.text = HPToPer.ToString() + " / 100 %";
    }
    // MP 업데이트
    public void UpdateMP(int NowMP, int MaxMP)
    {
        // MP값을 퍼센티지로 바꿔준다.
        float MPToPer = NowMP / MaxMP * 100.0f;
        // MP 슬라이더의 값을 바꿔준다.
        MP.value = MPToPer;
        // MP 슬라이더 텍스트의 내용을 바꿔준다.
        MPText.text = MPToPer.ToString() + " / 100 %";
    }

    public void UpdateLevel(int NowLevel)
    {
        Level.text = NowLevel.ToString();
    }

}
