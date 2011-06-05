/** 
 * @file  ProjectFile_test_SimpleRight.cpp
 *
 * @brief Implementation for SimpleRight testcase.
 */

#include <gtest/gtest.h>
#include <windows.h>
#include <tchar.h>

#include "UnicodeString.h"
#include "ProjectFile.h"

namespace
{
	/** @brief Projectfile to load. */
	static const TCHAR FileName[] = _T("TestData\\SimpleRight.WinMerge");
	/** @brief Right path we should get from file. */
	static const TCHAR RightPath[] = _T("C:\\Temp\\Right");

	// The fixture for testing paths functions.
	class ProjectFileSimpleRightTest : public testing::Test
	{
	protected:
		// You can remove any or all of the following functions if its body
		// is	empty.

		ProjectFileSimpleRightTest()
		{
			// You can do set-up work for each test	here.
		}

		virtual ~ProjectFileSimpleRightTest()
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
	TEST_F(ProjectFileSimpleRightTest, Load)
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
	 * @brief Read right path different ways.
	 */
	TEST_F(ProjectFileSimpleRightTest, GetRightPath)
	{
		// Has right path (only)
		BOOL bIsRight = m_pProjectFile->HasRight();
		EXPECT_EQ(TRUE, bIsRight);
		
		// Get right path without read-only info
		String right = m_pProjectFile->GetRight();
		EXPECT_TRUE(right.compare(RightPath) == 0);

		// Get right path with read-only info
		BOOL bReadOnly;
		right = m_pProjectFile->GetRight(&bReadOnly);
		EXPECT_TRUE(right.compare(RightPath) == 0);
		EXPECT_EQ(FALSE, bReadOnly);
	}

	/**
	 * @brief Make sure left path is not get.
	 */
	TEST_F(ProjectFileSimpleRightTest, GetLeftPath)
	{
		// We don't have left path
		BOOL bIsLeft = m_pProjectFile->HasLeft();
		EXPECT_EQ(FALSE, bIsLeft);

		// Get left path without read-only info
		String left = m_pProjectFile->GetLeft();
		EXPECT_TRUE(left.empty());

		// Get left path with read-only info
		BOOL bReadOnly;
		left = m_pProjectFile->GetLeft(&bReadOnly);
		EXPECT_TRUE(left.empty());
		EXPECT_EQ(FALSE, bReadOnly);
	}

	/**
	 * @brief Make sure subfolder inclusion is not get.
	 */
	TEST_F(ProjectFileSimpleRightTest, GetSubfolders)
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
	TEST_F(ProjectFileSimpleRightTest, GetFilter)
	{
		// We don't have a filter
		BOOL bHasFilter = m_pProjectFile->HasFilter();
		EXPECT_EQ(FALSE, bHasFilter);

		String filter = m_pProjectFile->GetFilter();
		EXPECT_TRUE(filter.empty());
	}
}
