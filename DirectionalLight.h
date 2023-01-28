#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>

/// <summary>
/// ���C�g
/// </summary>
class DirectionalLight
{
private://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		bool active = false;//�L���t���O
		XMVECTOR lightv;	//���C�g�ւ̕�����\��
		XMFLOAT3 lightcolor;//���C�g�̐F
	};

private://�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;

public:// �ÓI�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	/// <param name = "device">�f�o�C�X</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// �C���X�^���X
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static DirectionalLight* Create();

private://�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource>constBuff;
	//���C�g���������i�P�ʃx�N�g���j
	XMVECTOR lightdir = { 1,0,0,0 };
	//���C�g�F
	XMFLOAT3 lightcolor = { 1,1,1 };
	//�_�[�e�B�t���O
	bool dirty = false;
	//�L���t���O
	bool active = false;

public://�����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �萔�o�b�t�@�]��
	/// </summary>
	void TransferConstBuffer();

	void SetLightDir(const XMVECTOR& lightdir);
	XMVECTOR GetLightDir() { return lightdir; }
	void SetLightColor(const XMFLOAT3& lightcolor);
	XMFLOAT3 GetLightColor() { return lightcolor; }

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);
	
	/// <summary>
	/// �L���t���O���Z�b�g
	/// </summary>
	/// <param name = "lightdir">�L���t���O</param>
	inline void SetActive(bool active) { this->active = active; }

	/// <summary>
	/// �L���`�F�b�N
	/// </summary>
	/// <returns>�L���t���O</returns>
	inline bool isActive() { return active; }
};

