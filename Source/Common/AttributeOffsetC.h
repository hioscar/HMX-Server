#ifndef __ATTRIBUTE_OFFSET_H_
#define __ATTRIBUTE_OFFSET_H_



/*-------------------------------------------------------------------
 * @Brief : ���Թ����� 
 * 
 * @Author:hzd 2015:11:27
 *------------------------------------------------------------------*/

template<typename TAttributeType,int32_t TAttrMax>
class AttributeOffsetC
{
public:
	AttributeOffsetC(void){};
	~AttributeOffsetC(void){};

	/*-------------------------------------------------------------------
	 * @Brief : �����޸� 
	 * 
	 * @Author:hzd 2015:11:27
	 *------------------------------------------------------------------*/
	virtual bool SetAttribute(TAttributeType eAttributeType, const ValueType& vNewValue)
	{
		// ����Ƿ���ƫ��ֵ   
		if (m_sAttributeOffset[eAttributeType].nOffset && m_sAttributeOffset[eAttributeType].bCanSet)
		{
			SetAttribute(eAttributeType, vNewValue, false);
			return true;
		}
		else
		{
			return false;
		}
	}

	/*--------------------------------------------
	 *  @brief  : �����޸� 
	 *  @input	: bEnforce ǿ���޸� 
	 *  @return :	
	 *-------------------------------------------*/ 
	bool SetAttribute(TAttributeType eAttributeType, const ValueType& vNewValue, bool bEnforce)
	{
		// ����Ƿ���ƫ��ֵ  
		if (m_sAttributeOffset[eAttributeType].nOffset && (m_sAttributeOffset[eAttributeType].bCanSet || bEnforce))
		{
			// �Ƚ��¾�ֵ 
			if (memcmp(m_sAttributeOffset[eAttributeType].nOffset, &vNewValue, m_sAttributeOffset[eAttributeType].nSize))
			{
				// �����ֵ 
				ValueType vOldValue;
				memcpy(&vOldValue, m_sAttributeOffset[eAttributeType].nOffset, m_sAttributeOffset[eAttributeType].nSize);

				// ������ֵ 
				memcpy(m_sAttributeOffset[eAttributeType].nOffset, &vNewValue, m_sAttributeOffset[eAttributeType].nSize);

				// �ص� 
				if (m_sAttributeOffset[eAttributeType].hHandler)
				{
					m_sAttributeOffset[eAttributeType].hHandler(vOldValue, vNewValue);
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}


	bool GetAttribute(TAttributeType i_eAttributeType, ValueType& o_vValue)
	{
		// ����Ƿ���ƫ��ֵ 
		if (m_sAttributeOffset[i_eAttributeType].nOffset)
		{
			memcpy(&o_vValue, m_sAttributeOffset[i_eAttributeType].nOffset, m_sAttributeOffset[i_eAttributeType].nSize);

			return true;
		}
		else
		{
			return false;
		}
	}

	int32_t GetAttributeInt32(TAttributeType i_eAttributeType)
	{
		ValueType o_vValue;
		GetAttribute(i_eAttributeType,o_vValue);
		return o_vValue.nInt32;
	}

	int64_t GetAttributeInt64(TAttributeType i_eAttributeType)
	{
		ValueType o_vValue;
		GetAttribute(i_eAttributeType,o_vValue);
		return o_vValue.nInt64;
	}

	virtual void InitAttribute() = 0;

protected:

	AttributeOffset	m_sAttributeOffset[TAttrMax];		// 

};

#endif


