#pragma once

#include <sqlite3.h>
#include <stdexcept>
#include "Types.h"

class CSqliteStatement
{
public:
	CSqliteStatement() = default;

	CSqliteStatement(sqlite3* db, const char* query)
	{
		int result = sqlite3_prepare_v2(db, query, -1, &m_handle, nullptr);
		if(result != SQLITE_OK)
		{
			throw std::runtime_error("Failed to create statement.");
		}
	}

	//Non-copyable
	CSqliteStatement(const CSqliteStatement&) = delete;
	CSqliteStatement& operator =(const CSqliteStatement&) = delete;

	virtual ~CSqliteStatement()
	{
		Reset();
	}

	void Reset()
	{
		if(m_handle)
		{
			int result = sqlite3_finalize(m_handle);
			assert(result == SQLITE_OK);
			m_handle = nullptr;
		}
	}

	void BindText(int param, const char* value, bool isStatic = false)
	{
		int result = sqlite3_bind_text(m_handle, param, value, -1, isStatic ? SQLITE_STATIC : SQLITE_TRANSIENT);
		assert(result == SQLITE_OK);
	}

	void BindInteger(int param, uint32 value)
	{
		int result = sqlite3_bind_int(m_handle, param, value);
		assert(result == SQLITE_OK);
	}

	bool Step()
	{
		int result = sqlite3_step(m_handle);
		assert((result == SQLITE_ROW) || (result == SQLITE_DONE));
		return (result == SQLITE_ROW);
	}

	void StepWithResult()
	{
		bool hasRow = Step();
		assert(hasRow);
	}

	void StepNoResult()
	{
		bool hasRow = Step();
		assert(!hasRow);
	}

	operator sqlite3_stmt*() const
	{
		return m_handle;
	}

private:
	sqlite3_stmt* m_handle = nullptr;
};
