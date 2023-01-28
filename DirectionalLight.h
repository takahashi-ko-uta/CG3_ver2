#pragma once
#include <DirectXMath.h>
#include <d3d12.h>
#include <wrl.h>

/// <summary>
/// ライト
/// </summary>
class DirectionalLight
{
private://エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public://サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		bool active = false;//有効フラグ
		XMVECTOR lightv;	//ライトへの方向を表す
		XMFLOAT3 lightcolor;//ライトの色
	};

private://静的メンバ変数
	//デバイス
	static ID3D12Device* device;

public:// 静的メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name = "device">デバイス</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// インスタンス
	/// </summary>
	/// <returns>インスタンス</returns>
	static DirectionalLight* Create();

private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource>constBuff;
	//ライト光線方向（単位ベクトル）
	XMVECTOR lightdir = { 1,0,0,0 };
	//ライト色
	XMFLOAT3 lightcolor = { 1,1,1 };
	//ダーティフラグ
	bool dirty = false;
	//有効フラグ
	bool active = false;

public://メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 定数バッファ転送
	/// </summary>
	void TransferConstBuffer();

	void SetLightDir(const XMVECTOR& lightdir);
	XMVECTOR GetLightDir() { return lightdir; }
	void SetLightColor(const XMFLOAT3& lightcolor);
	XMFLOAT3 GetLightColor() { return lightcolor; }

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);
	
	/// <summary>
	/// 有効フラグをセット
	/// </summary>
	/// <param name = "lightdir">有効フラグ</param>
	inline void SetActive(bool active) { this->active = active; }

	/// <summary>
	/// 有効チェック
	/// </summary>
	/// <returns>有効フラグ</returns>
	inline bool isActive() { return active; }
};

