/* ========================================
    DX22Base/
    ------------------------------------
    2次元ベクトル用inlファイル
    ------------------------------------
    ※inlファイルはヘッダファイルに記載されているのと同じ
    　ヘッダーファイルの冗長化を防ぐために使用
    ------------------------------------
    Vector2.inl
========================================== */

// =============== インクルード ===================
#include "Vector2.h"

/* ========================================
	コンストラクタ関数
	-------------------------------------
	内容：デフォルトコンストラクタ
=========================================== */
template<typename T>
inline Vector2<T>::Vector2()
{
	this->x = 0;
	this->y = 0;
}

/* ========================================
    コンストラクタ関数
    -------------------------------------
    内容：2次元ベクトルの初期化
    -------------------------------------
    引数1：x	X座標
    引数2：y	Y座標
=========================================== */
template<typename T>
inline Vector2<T>::Vector2(T x, T y)
{
	this->x = x;
	this->y = y;

}

/* ========================================
    加算演算子
    -------------------------------------
    内容：ベクトル同士の加算
	-------------------------------------
    引数：other 加算するベクトル
	-------------------------------------
    戻値：加算結果
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const 
{
    return std::move(Vector2<T>(x + other.x, this->y + other.y));
}

/* ========================================
    減算演算子
    -------------------------------------
    内容：ベクトル同士の減算
	-------------------------------------
    引数：other 減算するベクトル
	-------------------------------------
    戻値：減算結果
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const 
{
    return std::move(Vector2<T>(this->x - other.x, this->y - other.y));
}

/* ========================================
    乗算演算子
    -------------------------------------
    内容：ベクトル同士の乗算
	-------------------------------------
    引数：other 乗算するベクトル
	-------------------------------------
    戻値：乗算結果
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::operator*(const Vector2<T>& other) const 
{
    return std::move(Vector2<T>(this->x * other.x, this->y * other.y));
}

/* ========================================
	乗算演算子(スカラー)
    -------------------------------------
    内容：ベクトルとスカラーの乗算
	-------------------------------------
    引数：scalar 乗算するスカラー
	-------------------------------------
    戻値：乗算結果
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::operator*(T scalar) const 
{
    return std::move(Vector2<T>(this->x * scalar, this->y * scalar));
}

/* ========================================
    除算演算子
    -------------------------------------
    内容：ベクトル同士の除算
	-------------------------------------
    引数：other 除算するベクトル
	-------------------------------------
    戻値：除算結果
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::operator/(const Vector2<T>& other) const 
{
    // 0での除算を防ぐ
    return std::move(Vector2<T>(
        other.x != 0 ? this->x / other.x : 0,
        other.y != 0 ? this->y / other.y : 0
    ));
}

/* ========================================
	除算演算子(スカラー)
    -------------------------------------
    内容：ベクトルとスカラーの除算
	-------------------------------------
    引数：scalar 除算するスカラー
	-------------------------------------
    戻値：除算結果
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::operator/(T scalar) const 
{
    return 
        scalar != 0 ?
        std::move(Vector2<T>(this->x / scalar, this->y / scalar))
        : Vector2<T>(0, 0);
}

/* ========================================
    加算代入演算子
    -------------------------------------
    内容：ベクトル同士の加算代入
	-------------------------------------
    引数：other 加算するベクトル
	-------------------------------------
    戻値：加算後のベクトル
=========================================== */
template<typename T>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other) 
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

/* ========================================
	減算代入演算子
	-------------------------------------
	内容：ベクトル同士の減算代入
	-------------------------------------
	引数：other 減算するベクトル
	-------------------------------------
	戻値：減算後のベクトル
=========================================== */
template<typename T>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

/* ========================================
	乗算代入演算子
	-------------------------------------
	内容：ベクトル同士の乗算代入
	-------------------------------------
	引数：other 乗算するベクトル
	-------------------------------------
	戻値：乗算後のベクトル
=========================================== */
template<typename T>
inline Vector2<T>& Vector2<T>::operator*=(const Vector2<T>& other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

/* ========================================
	乗算代入演算子(スカラー)
	-------------------------------------
	内容：ベクトルとスカラーの乗算代入
	-------------------------------------
	引数：scalar 乗算するスカラー
	-------------------------------------
	戻値：乗算後のベクトル
=========================================== */
template<typename T>
inline Vector2<T>& Vector2<T>::operator*=(T scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

/* ========================================
	除算代入演算子
	-------------------------------------
	内容：ベクトル同士の除算代入
	-------------------------------------
	引数：other 除算するベクトル
	-------------------------------------
	戻値：除算後のベクトル
=========================================== */
template<typename T>
inline Vector2<T>& Vector2<T>::operator/=(const Vector2<T>& other)
{
	// 0での除算を防ぐ
	this->x = other.x != 0 ? x / other.x : 0;
	this->y = other.y != 0 ? y / other.y : 0;
	return *this;
}

/* ========================================
	除算代入演算子(スカラー)
	-------------------------------------
	内容：ベクトルとスカラーの除算代入
	-------------------------------------
	引数：scalar 除算するスカラー
	-------------------------------------
	戻値：除算後のベクトル
=========================================== */
template<typename T>
inline Vector2<T>& Vector2<T>::operator/=(T scalar)
{
	// 0での除算を防ぐ
	if (scalar != 0)
	{
		this->x /= scalar;
		this->y /= scalar;
	}
	else
	{
		this->x = 0;
		this->y = 0;
	}

	return *this;
}

/* ========================================
	添え字演算子
	-------------------------------------
	内容：ベクトルの要素を取得
	-------------------------------------
	引数：index 要素番号
	-------------------------------------
	戻値：要素の値
=========================================== */
template<typename T>
inline T Vector2<T>::operator[](int index) const
{
	switch (index)
	{
	case 0: return this->x;
	case 1: return this->y;
	default: return 0;
	}
}

/* ========================================
	単項演算子(+)
	-------------------------------------
	内容：ベクトルの符号維持
	-------------------------------------
	戻値：符号維持したベクトル
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::operator+() const
{
	return *this;
}

/* ========================================
	単項演算子(-)
	-------------------------------------
	内容：ベクトルの符号反転
	-------------------------------------
	戻値：符号反転したベクトル
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::operator-() const
{
	return Vector2<T>(-this->x, -this->y);
}

/* ========================================
	比較演算子(==)
	-------------------------------------
	内容：ベクトル同士の等価比較
	-------------------------------------
	引数：other 比較するベクトル
	-------------------------------------
	戻値：true　一致
		  false 不一致
=========================================== */
template<typename T>
inline bool Vector2<T>::operator==(const Vector2<T>& other) const
{
	if (this->x != other.x) return false;
	if (this->y != other.y) return false;

	return true;
}

/* ========================================
	比較演算子(!=)
	-------------------------------------
	内容：ベクトル同士の非等価比較
	-------------------------------------
	引数：other 比較するベクトル
	-------------------------------------
	戻値：true　不一致
		  false 一致
=========================================== */
template<typename T>
inline bool Vector2<T>::operator!=(const Vector2<T>& other) const
{
	return !(*this == other);	// 等価比較の逆
}

/* ========================================
	比較演算子(<)
	-------------------------------------
	内容：ベクトル同士の比較(ベクトルの長さ)
	-------------------------------------
	引数：other	比較するベクトル
	-------------------------------------
	戻値：true	自身の方が小さい
		  false	自身の方が大きい
=========================================== */
template<typename T>
inline bool Vector2<T>::operator<(const Vector2<T>& other) const
{
	T thisLength = this->x * this->x + this->y * this->y;
	T otherLength = other.x * other.x + other.y * other.y;

	return thisLength < otherLength;
}

/* ========================================
	比較演算子(>)
	-------------------------------------
	内容：ベクトル同士の比較(ベクトルの長さ)
	-------------------------------------
	引数：other	比較するベクトル
	-------------------------------------
	戻値：true	自身の方が大きい
		  false	自身の方が小さい
=========================================== */
template<typename T>
inline bool Vector2<T>::operator>(const Vector2<T>& other) const
{
	T thisLength = this->x * this->x + this->y * this->y;
	T otherLength = other.x * other.x + other.y * other.y;

	return thisLength > otherLength;
}

/* ========================================
	比較演算子(<=)
	-------------------------------------
	内容：ベクトル同士の比較(ベクトルの長さ)
	-------------------------------------
	引数：other	比較するベクトル
	-------------------------------------
	戻値：true	自身の方が小さいか等しい
		  false	自身の方が大きい
=========================================== */
template<typename T>
inline bool Vector2<T>::operator<=(const Vector2<T>& other) const
{
	T thisLength = this->x * this->x + this->y * this->y;
	T otherLength = other.x * other.x + other.y * other.y;

	return thisLength <= otherLength;
}

/* ========================================
	比較演算子(>=)
	-------------------------------------
	内容：ベクトル同士の比較(ベクトルの長さ)
	-------------------------------------
	引数：other	比較するベクトル
	-------------------------------------
	戻値：true	自身の方が大きいか等しい
		  false	自身の方が小さい
=========================================== */
template<typename T>
inline bool Vector2<T>::operator>=(const Vector2<T>& other) const
{
	T thisLength = this->x * this->x + this->y * this->y;
	T otherLength = other.x * other.x + other.y * other.y;

	return thisLength >= otherLength;
}

/* ========================================
    ベクトル長さ取得関数
    -------------------------------------
    内容：ベクトルの長さを取得
	-------------------------------------
    戻値：ベクトルの長さ
=========================================== */
template<typename T>
inline double Vector2<T>::Length() const {
    return std::sqrt(x * x + y * y);
}

/* ========================================
	ベクトル長さ(2乗)取得関数
	-------------------------------------
	内容：ベクトルの長さの2乗を取得
	-------------------------------------
	戻値：ベクトルの長さの2乗
=========================================== */
template<typename T>
inline T Vector2<T>::LengthSq() const
{
	return x * x + y * y;
}

/* ========================================
	ベクトル正規化取得関数
	-------------------------------------
	内容：ベクトルを正規化した値を返す
	-------------------------------------
	戻値：ベクトルの正規化値(長さ1のベクトル)
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::Normalize() const
{
	T length = Length();
	if (length == 0)
	{
		*this = Vector2<T>(0, 0);	// 0での除算を防ぐ
	}
	*this = Vector2<T>(x / length, y / length);
}

/* ========================================
    内積取得関数
    -------------------------------------
    内容：ベクトル同士の内積を取得
	-------------------------------------
    引数：other 内積を取得するベクトル
	-------------------------------------
    戻値：内積結果
=========================================== */
template<typename T>
inline T Vector2<T>::Dot(const Vector2<T>& other) const {
    return this->x * other.x + this->y * other.y;
}

/* ========================================
	外積取得関数
	-------------------------------------
	内容：ベクトル同士の外積を取得
		　2次元ベクトルの外積は定義されていない
		　平行四辺形の面積を求めることができる
	-------------------------------------
	引数：other 外積を取得するベクトル
	-------------------------------------
	戻値：外積結果
=========================================== */
template<typename T>
inline T Vector2<T>::Cross(const Vector2<T>& other) const
{
	return this->x * other.y - this->y * other.x;
}

/* ========================================
	2点間距離取得関数
	-------------------------------------
	内容：2点間の距離を取得
	-------------------------------------
	引数：other 距離を取得するベクトル
	-------------------------------------
	戻値：2点間の距離
=========================================== */
template<typename T>
inline T Vector2<T>::Distance(const Vector2<T>& other) const
{
	T dx = this->x - other.x;
	T dy = this->y - other.y;

	return std::sqrt(dx * dx + dy * dy);
}

/* ========================================
	2点間距離(2乗)取得関数
	-------------------------------------
	内容：2点間の距離の2乗を取得
	-------------------------------------
	引数：other 距離を取得するベクトル
	-------------------------------------
	戻値：2点間の距離の2乗
=========================================== */
template<typename T>
inline T Vector2<T>::DistanceSq(const Vector2<T>& other) const
{
	T dx = this->x - other.x;
	T dy = this->y - other.y;

	return dx * dx + dy * dy;
}

/* ========================================
	角度取得関数(ラジアン)
	-------------------------------------
	内容：2つのベクトルがなす角度を取得(ラジアン)
	-------------------------------------
	引数：other 角度を取得するベクトル
	-------------------------------------
	戻値：2つのベクトルがなす角度(ラジアン)
=========================================== */
template<typename T>
inline double Vector2<T>::AngleRad(const Vector2<T>& other) const
{
	cos = this.Dot(other) / (this.Length() * other.Length());

	return std::acos(cos);
}

/* ========================================
	角度取得関数(度)
	-------------------------------------
	内容：2つのベクトルがなす角度を取得(度)
	-------------------------------------
	引数：other 角度を取得するベクトル
	-------------------------------------
	戻値：2つのベクトルがなす角度(度)
=========================================== */
template<typename T>
inline double Vector2<T>::AngleDeg(const Vector2<T>& other) const
{
	return this.AngleRad(other) * 180.0 / DirectX::XM_PI;
}

/* ========================================
	方向取得関数(ラジアン)
	-------------------------------------
	内容：引数ベクトルへの方向を取得(ラジアン)
	-------------------------------------
	引数：other 方向を取得するベクトル
	-------------------------------------
	戻値：引数ベクトルへの方向(ラジアン)
=========================================== */
template<typename T>
inline double Vector2<T>::DirectionRad(const Vector2<T>& other) const
{
	return std::atan2(other.y - this->y, other.x - this->x);
}

/* ========================================
	方向取得関数(度)
	-------------------------------------
	内容：引数ベクトルへの方向を取得(度)
	-------------------------------------
	引数：other 方向を取得するベクトル
	-------------------------------------
	戻値：引数ベクトルへの方向(度)
=========================================== */
template<typename T>
inline double Vector2<T>::DirectionDeg(const Vector2<T>& other) const
{
	return this->DirectionRad(other) * 180.0 / DirectX::XM_PI;
}

/* ========================================
	線形補間取得関数
	-------------------------------------
	内容：2つのベクトル間を線形補間
	-------------------------------------
	引数1：other	補間するベクトル
	引数2：t		補間係数
	-------------------------------------
	戻値：補間結果
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::Lerp(const Vector2<T>& other, float t) const
{
	return this + (other - this) * t;

}


/* ========================================
	DirectX::XMFLOAT2変換関数
	-------------------------------------
	内容：Vector2 -> DirectX::XMFLOAT2
	-------------------------------------
	戻値：変換後のXMFLOAT2
=========================================== */
template<typename T>
inline DirectX::XMFLOAT2 Vector2<T>::ToXMFLOAT2() const
{
	return DirectX::XMFLOAT2(static_cast<float>(this->x), static_cast<float>(this->y));
}

/* ========================================
	DirectX::XMFLOAT2変換関数
	-------------------------------------
	内容：DirectX::XMFLOAT2 -> Vector2
	-------------------------------------
	引数：other 変換するXMFLOAT2
	-------------------------------------
	戻値：変換後のVector2
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::ToVector2(const DirectX::XMFLOAT2& other) const
{
	return Vector2<T>(static_cast<T>(other.x), static_cast<T>(other.y));
}

/* ========================================
    ゼロベクトル取得関数
    -------------------------------------
    内容：ゼロベクトルを取得
	-------------------------------------
    戻値：ゼロベクトル
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::Zero() 
{
    return Vector2<T>(0, 0);
}

/* ========================================
    1ベクトル取得関数
    -------------------------------------
    内容：1ベクトルを取得
	-------------------------------------
    戻値：1ベクトル
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::One() 
{
    return Vector2<T>(1, 1);
}

/* ========================================
	上方向ベクトル取得関数
	-------------------------------------
	内容：上方向ベクトルを取得
	-------------------------------------
	戻値：上方向ベクトル
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::Up()
{
	return Vector2<T>(0, 1);
}

/* ========================================
	下方向ベクトル取得関数
	-------------------------------------
	内容：下方向ベクトルを取得
	-------------------------------------
	戻値：下方向ベクトル
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::Down()
{
	return Vector2<T>(0, -1);
}

/* ========================================
	右方向ベクトル取得関数
	-------------------------------------
	内容：右方向ベクトルを取得
	-------------------------------------
	戻値：右方向ベクトル
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::Right()
{
	return Vector2<T>(1, 0);
}

/* ========================================
	左方向ベクトル取得関数
	-------------------------------------
	内容：左方向ベクトルを取得
	-------------------------------------
	戻値：左方向ベクトル
=========================================== */
template<typename T>
inline Vector2<T> Vector2<T>::Left()
{
	return Vector2<T>(-1, 0);
}
