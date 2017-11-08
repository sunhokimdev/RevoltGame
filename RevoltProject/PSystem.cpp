#include "stdafx.h"
#include "PSystem.h"

//===================================================================
// - written by 정종훈
// - 파티클 시스템 요소
//===================================================================


const DWORD ST_Particle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_PSIZE;

PSystem::PSystem()
	:m_isUse(false)
{
	_device = 0;
	_vb = 0;
	_tex = 0;
}


PSystem::~PSystem()
{
	SAFE_RELEASE(_vb);
	SAFE_RELEASE(_tex);
}

void PSystem::Init(IDirect3DDevice9 * device, char* texFileName)
{
	_device = device;

	device->CreateVertexBuffer(_vbSize * sizeof(ST_Particle),
									D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
									ST_Particle::FVF,
									D3DPOOL_DEFAULT,
									&_vb,
									0);

	D3DXCreateTextureFromFileA(device, texFileName, &_tex);
}

void PSystem::Reset()
{
	std::list<ST_Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		ResetParticle(&(*i));
	}
}

void PSystem::AddParticle()
{
	ST_Attribute attribute;
	ResetParticle(&attribute);
	_particles.push_back(attribute);
}

void PSystem::PreRender()
{
	_device->SetRenderState(D3DRS_LIGHTING, false);
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	_device->SetRenderState(D3DRS_POINTSIZE, FtoDw(32.0f));
	_device->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(0.0f));

	// 거리에 따른 크기 제어
	_device->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
	_device->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

	// 텍스처의 알파 이용
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void PSystem::Render()
{
	if (!_particles.empty())
	{
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		PreRender();

		_device->SetTexture(0, _tex);
		_device->SetFVF(ST_Particle::FVF);
		_device->SetStreamSource(0, _vb, 0, sizeof(ST_Particle));

		if (_vbOffset >= _vbSize)	// 버텍스 버퍼를 벗어날 경우 처음부터 시작
			_vbOffset = 0;

		ST_Particle* v = 0;

		_vb->Lock(_vbOffset * sizeof(ST_Particle),
			_vbBatchSize * sizeof(ST_Particle),
			(void**)&v,
			_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		// 모든 파티클이 렌더링될 떄까지

		std::list<ST_Attribute>::iterator i;
		for (i = _particles.begin(); i != _particles.end(); i++)
		{
			if (i->_isAlive)
			{
				// 한 단계의 생존한 파티클을 다음 버텍스 버퍼 세그먼트로 복사
				v->_position = i->_position;
				v->_color = (D3DCOLOR)i->_color;
				v++;
				numParticlesInBatch++;	// 단계 카운터 증가

				if (numParticlesInBatch == _vbBatchSize) // 현재 단계가 모두 채워졌는지
				{
					// 버텍스 버퍼로 복사된 마지막 단계의 파티클을 그림
					_vb->Unlock();

					_device->DrawPrimitive(D3DPT_POINTLIST, _vbOffset, _vbBatchSize);

					// 단계가 그려지는 동안 다음 단계를 파티클로 채운다

					// 다음 단계의 처음 오프셋으로 이동한다.
					_vbOffset += _vbBatchSize;

					if (_vbOffset >= _vbSize)	// 경계를 넘으면 처음부터 시작
						_vbOffset = 0;

					_vb->Lock(_vbOffset * sizeof(ST_Particle),
						_vbBatchSize * sizeof(ST_Particle),
						(void**)&v,
						_vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0;
				} // << end if
			} // << end if
		} // << end for

		_vb->Unlock();

		// 일부만 채워진 단계 렌더링
		if (numParticlesInBatch)
		{
			_device->DrawPrimitive(D3DPT_POINTLIST, _vbOffset, numParticlesInBatch);
		}

		_vbOffset += _vbBatchSize;

		PostRender();

	} // << end if
}

void PSystem::PostRender()
{
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	_device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

bool PSystem::isEmpty()
{
	return _particles.empty();
}

bool PSystem::isDead()
{
	std::list<ST_Attribute>::iterator i;
	i = _particles.begin();

	while (i != _particles.end())
	{
		if (i->_isAlive == true)
			return false;
		i++;
	}

	return true;
}

DWORD PSystem::FtoDw(float f)
{
	return *((DWORD*)&f);
}

float PSystem::GetRandomFloat(float lowBound, float highBound)
{
	if (lowBound >= highBound)	// 잘못된 입력
		return lowBound;

	// [0, 1] 범위의 임의 float을 얻는다
	float f = (rand() % 10000) * 0.0001f;
	return (f * (highBound - lowBound) + lowBound);
}

void PSystem::GetRandomVector(D3DXVECTOR3* out, D3DXVECTOR3* min, D3DXVECTOR3* max)
{
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

void PSystem::removeDeadParticles()
{
	std::list<ST_Attribute>::iterator i;
	i = _particles.begin();

	while (i != _particles.end())
	{
		if (i->_isAlive == false)
		{
			i = _particles.erase(i);
		}
		else
		{
			i++;
		}
	}
}