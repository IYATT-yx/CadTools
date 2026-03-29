module;
#include "StdAfx.h"

export module UniversalPicker;

export class UniversalPicker
{
public:
	// 选择模式
	enum class SelectMode
	{
		Batch, // 批量模式：选完按回车一起处理
		Immediate // 即时模式：点一个处理一个
	};

	// 处理函数原型
	using EntityProcessor = std::function<void(const AcDbObjectId)>;
	// 实体类型数组
	using AcRxClassVector = std::vector<AcRxClass*>;
	using AcRxClassVectorPtr = AcRxClassVector*;

private:
	/**
	 * @brief 构建过滤器
	 * @param arcv 实体类型数组指针
	 * @return 过滤器链表，调用者负责释放
	 */
	static resbuf* buildFilter(UniversalPicker::AcRxClassVectorPtr arcv);

	/**
	 * @brief 批量选择处理
	 * @param arcv 实体类型数组指针，用于过滤选择对象 
	 * @param processor 处理函数，接受一个实体ID参数
	 */
	static void batchSelect(UniversalPicker::AcRxClassVectorPtr arcv, UniversalPicker::EntityProcessor processor);

	/**
	 * @brief 即时选择处理
	 * @param arcv 实体类型数组指针，用于过滤选择对象 
	 * @param processor 处理函数，接受一个实体ID参数
	 */
	static void immediateSelect(UniversalPicker::AcRxClassVectorPtr arcv, UniversalPicker::EntityProcessor processor);

	/**
	 * @brief 释放过滤器链表
	 * @param filterRb 过滤器链表，调用者负责传入，函数内部会释放
	 */
	static void freeFilter(resbuf* filterRb);

public:
	/**
	 * @brief 运行选择器
	 * @param arcv 实体类型数组指针，用于过滤选择对象 
	 * @param processor 处理函数，接受一个实体ID参数
	 * @param prompt 提示信息
	 * @param defaultSelectMode 默认选择模式，默认为批量模式
	 * @param lockSelectMode 是否锁定选择模式，默认为不锁定
	 */
	static void run(UniversalPicker::AcRxClassVectorPtr arcv, UniversalPicker::EntityProcessor processor, const ACHAR* prompt, UniversalPicker::SelectMode defaultSelectMode = UniversalPicker::SelectMode::Batch, bool lockSelectMode = false);
};

