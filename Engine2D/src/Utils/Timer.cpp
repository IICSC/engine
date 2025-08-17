#include "Engine2D/Utils/Timer.h"
#include <SDL.h>
#include <algorithm>

namespace Engine2D {

Timer::Timer()
    : m_startTicks(0)
    , m_pausedTicks(0)
    , m_frameStartTime(0)
    , m_lastFrameTime(0)
    , m_frameRateCap(0)
    , m_deltaTime(0.0f)
    , m_fps(0.0f)
    , m_frameCount(0)
    , m_running(false)
    , m_paused(false) {
}

Timer::~Timer() = default;

void Timer::initialize() {
    m_startTicks = 0;
    m_pausedTicks = 0;
    m_frameStartTime = 0;
    m_lastFrameTime = 0;
    m_frameRateCap = 0;
    m_deltaTime = 0.0f;
    m_fps = 0.0f;
    m_frameCount = 0;
    m_running = false;
    m_paused = false;
}

void Timer::startFrame() {
    m_frameStartTime = SDL_GetTicks();
    
    if (m_lastFrameTime > 0) {
        m_deltaTime = (m_frameStartTime - m_lastFrameTime) / 1000.0f;
        
        // 计算帧率（使用移动平均）
        if (m_deltaTime > 0) {
            float currentFPS = 1.0f / m_deltaTime;
            m_fps = m_fps * 0.9f + currentFPS * 0.1f; // 平滑帧率计算
        }
    }
    
    m_lastFrameTime = m_frameStartTime;
}

void Timer::endFrame() {
    m_frameCount++;
}

void Timer::start() {
    m_running = true;
    m_paused = false;
    m_startTicks = SDL_GetTicks();
    m_pausedTicks = 0;
}

void Timer::pause() {
    if (m_running && !m_paused) {
        m_paused = true;
        m_pausedTicks = SDL_GetTicks() - m_startTicks;
        m_startTicks = 0;
    }
}

void Timer::resume() {
    if (m_running && m_paused) {
        m_paused = false;
        m_startTicks = SDL_GetTicks() - m_pausedTicks;
        m_pausedTicks = 0;
    }
}

void Timer::stop() {
    m_running = false;
    m_paused = false;
    m_startTicks = 0;
    m_pausedTicks = 0;
}

void Timer::reset() {
    m_startTicks = SDL_GetTicks();
    m_pausedTicks = 0;
    m_frameCount = 0;
}

uint32_t Timer::getTicks() const {
    if (m_running) {
        if (m_paused) {
            return m_pausedTicks;
        } else {
            return SDL_GetTicks() - m_startTicks;
        }
    }
    return 0;
}

float Timer::getDeltaTime() const {
    return m_deltaTime;
}

float Timer::getDeltaTimeMS() const {
    return m_deltaTime * 1000.0f;
}

float Timer::getFPS() const {
    return m_fps;
}

uint64_t Timer::getFrameCount() const {
    return m_frameCount;
}

bool Timer::isRunning() const {
    return m_running;
}

bool Timer::isPaused() const {
    return m_paused;
}

void Timer::setFrameRateCap(uint32_t fps) {
    m_frameRateCap = fps;
}

uint32_t Timer::getFrameRateCap() const {
    return m_frameRateCap;
}

void Timer::delayFrame() {
    if (m_frameRateCap > 0) {
        uint32_t frameTime = SDL_GetTicks() - m_frameStartTime;
        uint32_t targetFrameTime = 1000 / m_frameRateCap;
        
        if (frameTime < targetFrameTime) {
            SDL_Delay(targetFrameTime - frameTime);
        }
    }
}

} // namespace Engine2D 