package com.example.ui.model

import java.util.UUID

data class ChatMessage(
    val id: String = UUID.randomUUID().toString(),
    val text: String,
    val isUser: Boolean,
    val timestamp: Long = System.currentTimeMillis(),
    val speedTokensPerSec: Float = 0f,
    val generationTimeMs: Long = 0L,
    val tokenCount: Int = 0
)

data class ModelInfo(
    val name: String,
    val path: String,
    val sizeBytes: Long,
    val sizeFormatted: String,
    val isLoaded: Boolean,
    val quantization: String = "Q4_K_M",
    val parameterSize: String = "1B",
    val estimatedRamMb: Int = 650,
    val isSafeFor32Bit: Boolean = true,
    val warningMessage: String? = null
)

data class HardwareInfo(
    val deviceModel: String,
    val board: String,
    val cpuArch: String,
    val is32BitKernelOrUserland: Boolean,
    val androidVersion: String,
    val apiLevel: Int,
    val totalRamMb: Long,
    val availableRamMb: Long,
    val availableRamPercent: Int
)

data class EngineConfig(
    val threadCount: Int = 4,
    val contextLength: Int = 512,
    val temperature: Float = 0.7f,
    val topP: Float = 0.9f,
    val seed: Int = 42
)

data class HuggingFaceModelRecommendation(
    val title: String,
    val repoId: String,
    val fileName: String,
    val parameterSize: String,
    val quantType: String,
    val fileSizeBytes: Long,
    val fileSizeFormatted: String,
    val ramRequirementMb: Int,
    val speedRating: String,
    val reasoningRating: String,
    val description: String,
    val directDownloadUrl: String
)
