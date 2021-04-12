using System.Collections;
using UnityEngine;

// 총을 구현한다
public class Gun : MonoBehaviour {
    // 총의 상태를 표현하는데 사용할 타입을 선언한다
    public enum State {
        Ready, // 발사 준비됨
        Empty, // 탄창이 빔
        Reloading // 재장전 중
    }

    public State state { get; private set; } // 현재 총의 상태

    public Transform fireTransform; // 총알이 발사될 위치

    public ParticleSystem muzzleFlashEffect; // 총구 화염 효과
    public ParticleSystem shellEjectEffect; // 탄피 배출 효과

    private LineRenderer bulletLineRenderer; // 총알 궤적을 그리기 위한 렌더러

    private AudioSource gunAudioPlayer; // 총 소리 재생기
    public AudioClip shotClip; // 발사 소리
    public AudioClip reloadClip; // 재장전 소리

    public float damage = 25; // 공격력
    private float fireDistance = 50f; // 사정거리

    public int ammoRemain = 100; // 남은 전체 탄약
    public int magCapacity = 25; // 탄창 용량
    public int magAmmo; // 현재 탄창에 남아있는 탄약


    public float timeBetFire = 0.12f; // 총알 발사 간격
    public float reloadTime = 1.8f; // 재장전 소요 시간
    private float lastFireTime; // 총을 마지막으로 발사한 시점


    private void Awake() {
        // 사용할 컴포넌트들의 참조를 가져오기
        gunAudioPlayer = GetComponent<AudioSource>();
        bulletLineRenderer = GetComponent<LineRenderer>();
        
        // 사용할 점을 두개로 변경하겠다.
        bulletLineRenderer.positionCount = 2;

        // 라인 렌더러를 비활성화하겠다.
        bulletLineRenderer.enabled = false;
    }

    private void OnEnable() {
        // 총 상태 초기화
        magAmmo = magCapacity;

        state = State.Ready;
        // 마지막으로 총을 쏜 시점을 초기화
        lastFireTime = 0;
    }

    // 발사 시도
    public void Fire() {

        // Fire가 일어날 수 있는 상황
        // State 가 발사 가능한 상태 - READY
        // 그리고 마지막 총 발사 시점에서 timeBetFire이상의 시간이 지났을 경우에
        if (state == State.Ready && Time.time >= lastFireTime + timeBetFire)
        {
            // 마지막으로 발사한 시간을 갱신하고
            lastFireTime = Time.time;
            // 실제 발사를 처리하는 메소드를 실행한다.
            Shot();
        }
    }

    // 실제 발사 처리
    private void Shot() {
        // RayCast에서 발생한 충돌 정보를 저장하자
        RaycastHit hit;

        //  탄알이 맞은 곳을 저장할 변수
        Vector3 hitPosition = Vector3.zero;

        // Raycast(시작 지점, 방향, 충동 정보, 사정거리)
        if(Physics.Raycast(fireTransform.position,fireTransform.forward, out hit,fireDistance))
        {
            // Ray가 어떤 오브젝트와 충돌했을 경우

            // 충돌한 상대방으로 부터 IDamageable Component를 가지고 온다.
            IDamageable target = hit.collider.GetComponent<IDamageable>();
            
            // 충돌한 상대방으로부터 컴포넌트를 가지고 오는데에 성공했다면
            if(target != null)
            {
                // 상대방의 OnDamage 메소드를 실행시켜 상대방에 데미지를 입힌다.
                target.OnDamage(damage, hit.point, hit.normal);
            }

            hitPosition = hit.point;
        }
        else 
        {
            // Ray가 어떤 오브젝트와 충돌하지 않았을 경우
            // 탄알의 최대 사정거리까지 날아갔을 때의 위치를 충돌 위치로 사용한다
            hitPosition = fireTransform.position + fireTransform.forward * fireDistance;
        }

        // 발사이펙트 재생을 시작
        StartCoroutine(ShotEffect(hitPosition));

        // 남은 탄알 수를 차감
        magAmmo--;

        if(magAmmo<=0)
        {
            // 탄창에 남은 탄알이 없다면 총의 현재 상태를 Empty로 만들어준다.
            state = State.Empty;
        }
    }

    // 발사 이펙트와 소리를 재생하고 총알 궤적을 그린다
    private IEnumerator ShotEffect(Vector3 hitPosition) {

        // 총구 화연 효과 재생
        muzzleFlashEffect.Play();
        // 탄피 배출 효과 재생
        shellEjectEffect.Play();
        // 총격 소리 재생
        gunAudioPlayer.PlayOneShot(shotClip);

        // 선의 시작점은 총구의 위치가 된다. - 0
        bulletLineRenderer.SetPosition(0, fireTransform.position);
        // 선의 끝나는 점은 입력으로 들어온 충돌위치로 설정한다. - 1
        bulletLineRenderer.SetPosition(1, hitPosition);

        // 라인 렌더러를 활성화하여 총알 궤적을 그린다
        bulletLineRenderer.enabled = true;

        // 0.03초 동안 잠시 처리를 대기
        yield return new WaitForSeconds(0.03f);

        // 라인 렌더러를 비활성화하여 총알 궤적을 지운다
        bulletLineRenderer.enabled = false;
    }

    // 재장전 시도
    public bool Reload() {
        
        if(state == State.Reloading || ammoRemain <=0 || magAmmo > magCapacity)
        {
            // 이미 재장전중이거나
            // 남은 보유탄환이 없거나
            // 이미 탄창이 가득차있을 경우
            return false;
        }

        // 재장전 처리를 해준다.
        StartCoroutine(ReloadRoutine());
        return true;
    }

    // 실제 재장전 처리를 진행
    private IEnumerator ReloadRoutine() {
        // 현재 상태를 재장전 중 상태로 전환
        state = State.Reloading;

        // 재장전 소리를 실행한다
        gunAudioPlayer.PlayOneShot(reloadClip);

        // 재장전 소요 시간 만큼 처리를 쉬기
        yield return new WaitForSeconds(reloadTime);

        // 탄창에 채워야 하는 탄알의 개수를 계산한다.
        int ammoToFill = magCapacity - magAmmo; // 탄창에 채울 수 있는 최대량 - 현재 탄창에 남은 탄알 개수

        // 탄창에 채워야할 탄알이 남은 탄알보다 많다면 
        // 채워야 할 탄알 수를 남은 탄알 수에 맞춰 줄여야 한다.
        if(ammoRemain < ammoToFill)
        {                                           // 예를 들어 나는 25개를 채울 수 있는 탄창인데
            ammoToFill = ammoRemain;                // 남은게 24개면 24개밖에 못채우니까 채워야하는 개수를 변경해야 한다.
        }

        // 탄창을 채워준다.
        magAmmo += ammoToFill;
        // 남은 탄알에서 채운만큼 빼줘야한다.
        ammoRemain -= ammoToFill;
        // 총의 현재 상태를 발사 준비된 상태로 변경
        state = State.Ready;
    }
}