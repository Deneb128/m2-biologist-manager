//find ESex GET_SEX(LPCHARACTER ch)
//add above
//SEND BIOLOGIST REQUEST
bool CHARACTER::IsNextBiologistRequestPulse() const { return (m_biologistRequestPulse == 0 || (m_biologistRequestPulse < thecore_pulse())); }
void CHARACTER::UpdateBiologistRequestPulse() { m_biologistRequestPulse = thecore_pulse() + (PASSES_PER_SEC(1) / 5); }
