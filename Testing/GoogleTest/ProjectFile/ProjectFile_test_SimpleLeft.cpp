/** 
 * @file  ProjectFile_test_SimpleLeft.cpp
 *
 * @brief Implementation for SimpleLeft testcase.
 */

#include <gtest/gtest.h>
#include <windows.h>
#include <tchar.h>

#include "UnicodeString.h"
#include "ProjectFile.h"

namespace
{
	/** @brief Projectfile to load. */
	static const TCHAR FileName[] = _T("TestData\\SimpleLeft.WinMerge");
	/** @brief Left path we should get from file. */
	static const TCHAR LeftPath[] = _T("C:\\Temp\\Left");

	// The fixture for testing paths functions.
	class ProjectFileSimpleLeftTest : public testing::Test
	{
	protected:
		// You can remove any or all of the following functions if its body
		// is	empty.

		ProjectFileSimpleLeftTest()
		{
			// You can do set-up work for each test	here.
		}

		virtual ~ProjectFileSimpleLeftTest()
		{
			// You can do clean-up work	that doesn't throw exceptions here.
		}

		// If	the	constructor	and	destructor are not enough for setting up
		// and cleaning up each test, you can define the following methods:

		virtual void SetUp()
		{
			// Code	here will be called	immediately	after the constructor (right
			// before each test).
			m_pProjectFile = new ProjectFile;

			String sError;
			BOOL success = m_pProjectFile->Read(FileName, &sError);
		}

		virtual void TearDown()
		{
			// Code	here will be called	immediately	after each test	(right
			// before the destructor).
			delete m_pProjectFile;
		}

		// Objects declared here can be used by all tests in the test case for ProjectFile.
		ProjectFile *m_pProjectFile;
	};

	/**
	 * @brief Load the projectfile.
	 */
	TEST_F(ProjectFileSimpleLeftTest, Load)
	{
		String sError;
		
		// setUp already created the project file for us, but this
		// test is for testing creation and loading..
		if (m_pProjectFile)
			delete m_pProjectFile;
		m_pProjectFile = new ProjectFile;
		EXPECT_TRUE(m_pProjectFile != NULL);

		BOOL success = m_pProjectFile->Read(FileName, &sError);

		// Must succeed
		EXPECT_EQ(TRUE, success);
		EXPECT_TRUE(sError.empty());
	}

	/**
	 * @brief Read left path different ways.
	 */
	TEST_F(ProjectFileSimpleLeftTest, GetLeftPath)
	{
		// Has left path (only)
		BOOL bIsLeft = m_pProjectFile->HasLeft();
		EXPECT_EQ(TRUE, bIsLeft);
		
		// Get left path without read-only info
		String left = m_pProjectFile->GetLeft();
		EXPECT_TRUE(left.compare(LeftPath) == 0);

		// Get left path with read-only info
		BOOL bReadOnly;
		left = m_pProjectFile->GetLeft(&bReadOnly);
		EXPECT_TRUE(left.compare(LeftPath) == 0);
		EXPECT_EQ(FALSE, bReadOnly);
	}

	/**
	 * @brief Make sure right path is not get.
	 */
	TEST_F(ProjectFileSimpleLeftTest, GetRightPath)
	{
		// We don't have right path
		BOOL bIsRight = m_pProjectFile->HasRight();
		EXPECT_EQ(FALSE, bIsRight);

		// Get right path without read-only info
		String right = m_pProjectFile->GetRight();
		EXPECT_TRUE(right.empty());

		// Get right path with read-only info
		BOOL bReadOnly;
		right = m_pProjectFile->GetRight(&bReadOnly);
		EXPECT_TRUE(right.empty());
		EXPECT_EQ(FALSE, bReadOnly);
	}

	/**
	 * @brief Make sure subfolder inclusion is not get.
	 */
	TEST_F(ProjectFileSimpleLeftTest, GetSubfolders)
	{
		// We don't have a subfolders
		BOOL bHasSubfolders = m_pProjectFile->HasSubfolders();
		EXPECT_EQ(FALSE, bHasSubfolders);

		// Returns -1 if not set
		int subfolders = m_pProjectFile->GetSubfolders();
		EXPECT_EQ(-1, subfolders);
	}

	/**
	 * @brief Make sure filter is not get.
	 */
	TEST_F(ProjectFileSimpleLeftTest, GetFilter)
	{
		// We don't have a filter
		BOOL bHasFilter = m_pProjectFile->HasFilter();
		EXPECT_EQ(FALSE, bHasFilter);

		String filter = m_pProjectFile->GetFilter();
		EXPECT_TRUE(filter.empty());
	}
}
