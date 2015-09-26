package com.turbosanta.backend.logging;

import com.turbosanta.backend.logging.Messages.Message;
import com.turbosanta.backend.logging.streams.InStream;

public abstract class AbstractConsumerFactory<F extends AbstractConsumerFactory<F, C>, C extends Consumer> {
  public abstract F setMessageStream(InStream<Message> stream);

  public abstract C build();
}
