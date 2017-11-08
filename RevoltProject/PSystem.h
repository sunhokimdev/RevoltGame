#pragma once

//===================================================================
// - written by 정종훈
// - 파티클 시스템 요소
//===================================================================

struct ST_Particle
{
	D3DXVECTOR3		_position;
	D3DXCOLOR		_color;
	//float			_size;
	static const DWORD FVF;
};

struct ST_Attribute
{
	D3DXVECTOR3 _position;			// 월드 스페이스 내의 파티클 위치
	D3DXVECTOR3 _velocity;			// 파티클의 속도(보통 초당 이동 단위로 기록)
	D3DXVECTOR3 _acceleration;		// 파티클의 가속(보통 초당 이동 단위로 기록)
	float		_lifeTime;			// 파티클이 소멸할 때까지 유지되는 시간
	float		_age;				// 파티클의 현재 나이
	D3DXCOLOR	_color;				// 파티클의 컬러
	D3DXCOLOR	_colorFade;			// 파티클의 컬러가 시간의 흐름에 따라 퇴색하는 방법
	bool		_isAlive;			// 파티클이 생존확인

	ST_Attribute()
	{
		_lifeTime = 0.0f;
		_age = 0.0f;
		_isAlive = true;
	}
};


class PSystem
{
public:
	PSystem();
	virtual ~PSystem();

	virtual void Init(IDirect3DDevice9* device, char* texFileName);
	virtual void Reset();													// 모든 파티클 속성 리셋
	virtual void ResetParticle(ST_Attribute* attribute) = 0;				// 한 파티클 속성 리셋
	virtual void AddParticle();												// 파티클 추가

	virtual void SetPosition(D3DXVECTOR3* origin) = 0;

	virtual void Update(float timeDelta) = 0;

	virtual void PreRender();						// 렌더링에 앞서 지정해야 할 초기 렌더 상태를 지정
	virtual void Render();
	virtual void PostRender();						// 특정 파티클 시스템이 지정했을 수 있는 렌더 상태를 복구하는데 이용

	bool isEmpty();					// 파티클이 없는 경우 true
	bool isDead();					// 파티클이 모두 죽은 경우 true ( 파티클이 있지만 죽은상태)

	SYNTHESIZE(bool, m_isUse, IsUse);

	DWORD FtoDw(float f);

	// 무작위성을 위해..
	float GetRandomFloat(float lowBound, float highBound);
	void GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max);

protected:
	virtual void removeDeadParticles();		// 죽은 파티클을 리스트에서 제거

	IDirect3DDevice9*	_device;
	D3DXVECTOR3			_origin;	// 파티클이 시작되는 곳

	float				_emitRate;	// 새로운 파티클이 추가되는 비율(보통 초당 파티클 수로 기록)
	float				_size;		// 시스템 내 모든 파티클 크기
	IDirect3DTexture9*	_tex;		// 시스템 내 모든 파티클 속성의 리스트
	IDirect3DVertexBuffer9* _vb;
	std::list<ST_Attribute>	_particles;
	int					_maxParticles;		// 주어진 시간동안 시스템이 가질수 있는 최대 파티클의 수

	DWORD	_vbSize;			// 버텍스버퍼가 보관할 수 있는 파티클의 수
	DWORD	_vbOffset;			// 버텍스 버퍼에서 복사를 시작할 파티클 내 다음 단계로의 오프셋
	DWORD	_vbBatchSize;		// 하나의 단계에 정의된 파티클의 수
};

