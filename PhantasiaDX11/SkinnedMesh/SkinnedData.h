#pragma once

#include "d3dUtil.h"
#include <map>

struct Keyframe
{
	Keyframe();
	~Keyframe();

	float TimePos;
	XMFLOAT3 Translation;
	XMFLOAT3 Scale;
	XMFLOAT4 RotationQuat;
};

struct BoneAnimation
{
	float GetStartTime() const;
	float GetEndTime() const;

	void Interpolate(float t, XMFLOAT4X4& M) const;

	std::vector<Keyframe> Keyframes;
};

struct AnimationClip
{
	float GetClipStartTime() const;
	float GetClipEndTime() const;

	void Interpolate(float t, std::vector<XMFLOAT4X4>& bondeTransforms) const;

	std::vector<BoneAnimation> BoneAnimations;
};

class SkinnedData
{
public:
	UINT BoneCount() const;

	float GetClipStartTime(const std::string& clipName) const;
	float GetClipEndTime(const std::string& clipName) const;

	void Set(
		std::vector<int>& boneHierarchy,
		std::vector<XMFLOAT4X4>& boneOffsets,
		std::map<std::string, AnimationClip>& animations);

	void GetFinalTransforms(const std::string& clipName, float timePos,
		std::vector<XMFLOAT4X4>& finalTransforms) const;

private:
	std::vector<int> mBoneHierarchy;

	std::vector<XMFLOAT4X4> mBoneOffsets;

	std::map<std::string, AnimationClip> mAnimations;
};